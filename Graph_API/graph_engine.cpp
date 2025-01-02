//
//  graph_engine.cpp
//  Graph_API
//
//  Created by ChanningTong on 1/1/25.
//

#include <vector>
#include <memory>
#include "graph_engine.hpp"

SpatialPrimitive::SpatialPrimitive(const std::vector<Point>& inputVertex,GLenum shp,Shader* shader, int elementSize):
Primitive(inputVertex,shp,shader){
    SpatialRange range = SpatialRange(extent.left,extent.botton,extent.right - extent.left,extent.top - extent.botton);
    indexTree = std::make_shared<QuadTree<size_t>>(range,10);
    for (size_t i = 0; i < vertexNum; i += elementSize){
        float x = 0,y = 0;
        for (int k = 0; k < elementSize; k++){
            size_t index = (i + k) * stride;
            x += vertices[index];
            y += vertices[index + 1];
        }
        x /= elementSize;
        y /= elementSize;
        indexTree->insert(x,y,i);
    }
}
namespace transport{
std::shared_ptr<CityPoints> BuildVisualPoints(WUSG::Graph<valueType>& graph){
    std::vector<Point> vertices;
    std::vector<int> ID;
    vertices.reserve(graph.vertexCount());
    ID.reserve(graph.vertexCount());
    static constexpr glm::vec3 cityColor = glm::vec3(1.0,0.63,0.48);
    auto visit = [](const WUSG::Vertex<valueType>& node,std::vector<Point>* verticesArray,std::vector<int>* IDarray){
        valueType x = node.x, y = node.y;
        verticesArray->push_back(Point(glm::vec3(x,y,0.0),cityColor));
        IDarray->push_back(node.id);
    };
    auto binded = std::bind(visit, std::placeholders::_1, &vertices,&ID);
    WUSG::BFS(graph, graph.getStartVertex(), binded);
    return std::make_shared<CityPoints>(vertices,0.015,ID);
}
std::shared_ptr<Roads> BuildVisualRoads(WUSG::Graph<valueType>& graph){
    std::vector<Point> vertices;
    std::vector<VertexPair> pairArray;
    vertices.reserve(graph.edgeCount());
    static constexpr glm::vec3 roadColor = glm::vec3(0.69,0.93,0.94);
    const std::set<VertexPair>& pairs = graph.getVertexpairs();
    for (std::set<VertexPair>::const_iterator vpair = pairs.begin(); vpair != pairs.end(); vpair++){
        int id1 = vpair->first, id2 = vpair->second;
        WUSG::Vertex<valueType> temp1(id1),temp2(id2);
        WUSG::Vertex<valueType> v1(graph.getVertex(temp1)),v2(graph.getVertex(temp2));
        vertices.push_back(Point(glm::vec3(v1.x,v1.y,0.0),roadColor));
        vertices.push_back(Point(glm::vec3(v2.x,v2.y,0.0),roadColor));
        pairArray.push_back(*vpair);
    }
    return std::make_shared<Roads>(vertices,0.08,pairArray);
}
void processOperator(GLFWwindow* window){
    Camera2D& camera = Camera2D::getView();
    if (!gui::DrawPopup())
        camera.processKeyboard(window);
    if (RouteSystem::getSystem().graph != nullptr){
        gui::processWorkspace();
        processMouse();
    }
}
void processMouse(){
    using Node = transport::Node<valueType>;
    using Vertex = WUSG::Vertex<valueType>;
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    if (buffer.pressLeft){
        glm::vec2 checkPos = buffer.checkPos;
        RouteSystem& system = RouteSystem::getSystem();
        int ID = system.citys->getClick(checkPos.x, checkPos.y);
        if (ID > 0){
            buffer.currentNode = std::make_shared<Node>(system.graph->getVertex(Vertex(ID)));
        }else{
            VertexPair pair = system.roads->getClick(checkPos.x, checkPos.y);
            Vertex v1 = system.graph->getVertex(Vertex(pair.first)), v2 = system.graph->getVertex(Vertex(pair.second));
            if (pair.first > 0 && pair.second > 0)
                buffer.currentNode = std::make_shared<Node>(v1,v2,system.graph->getWeight(v1,v2));
            else
                buffer.currentNode = nullptr;
        }
        buffer.pressLeft = false;
    }
}
void CityPoints::draw() const{
    shader ->use();
    GLuint projectionLoc = glGetUniformLocation(shader->program, "projection");
    GLuint viewLoc = glGetUniformLocation(shader->program, "view");
    GLuint modelLoc = glGetUniformLocation(shader->program, "model");
    Camera2D& camera = Camera2D::getView();
    glm::mat4 projection = camera.getProjectionMatrix();
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 model = transMat;
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
    GLuint radiusLoc = glGetUniformLocation(shader->program, "radius");
    GLuint transparentLoc = glGetUniformLocation(shader->program, "transparent");
    glUniform1f(radiusLoc,radius * camera.getZoom());
    glUniform1f(transparentLoc,1.0f);
    glBindVertexArray(VAO);
    glDrawArrays(shape, 0, static_cast<GLsizei>(vertexNum));
    glBindVertexArray(0);
}
int CityPoints::getClick(double x,double y){
    std::vector<size_t> result = searchWindow(x,y);
    int id = -1;
    if (result.empty())
        return id;
    float distance = std::numeric_limits<float>::max();
    for (std::vector<size_t>::iterator it = result.begin(); it != result.end(); it++){
        size_t index = *it;
        float px = vertices[index * stride],py = vertices[index * stride + 1];
        float pdis = std::abs(px - x) + std::abs(py - y);
        if (pdis < clickRange * 2 && pdis < distance){ // get the nearest point
            distance = pdis;
            id = vertexID[index];
        }
    }
    return id;
}

void Roads::draw() const{
    shader ->use();
    GLuint projectionLoc = glGetUniformLocation(shader->program, "projection");
    GLuint viewLoc = glGetUniformLocation(shader->program, "view");
    GLuint modelLoc = glGetUniformLocation(shader->program, "model");
    Camera2D& camera = Camera2D::getView();
    glm::mat4 projection = camera.getProjectionMatrix();
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 model = transMat;
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
    GLuint thicknessLoc = glGetUniformLocation(shader->program, "thickness");
    GLuint transparentLoc = glGetUniformLocation(shader->program, "transparent");
    glUniform1f(thicknessLoc,thickness * camera.getZoom());
    glUniform1f(transparentLoc,1.0f);
    glBindVertexArray(VAO);
    glDrawArrays(shape, 0, static_cast<GLsizei>(vertexNum));
    glBindVertexArray(0);
}
VertexPair Roads::getClick(double x,double y){
    std::vector<size_t> result = searchWindow(x,y);
    VertexPair id = std::make_pair(-1,-1);
    if (result.empty())
        return id;
    float distance = std::numeric_limits<float>::max();
    for (std::vector<size_t>::iterator it = result.begin(); it != result.end(); it++){
        size_t index1 = *it,index2 = *it + 1;
        float px1 = vertices[index1 * stride],py1 = vertices[index1 * stride + 1];
        float px2 = vertices[index2 * stride],py2 = vertices[index2 * stride + 1];
        float A = py2 - py1;
        float B = px1 - px2;
        float C = px2 * py1 - px1 * py2;
        float distanceToLine = std::abs(A * x + B * y + C) / std::sqrt(A * A + B * B);
        if (distanceToLine < clickRange) {
            float lineLength = std::sqrt((px2 - px1) * (px2 - px1) + (py2 - py1) * (py2 - py1));
            float projection = ((x - px1) * (px2 - px1) + (y - py1) * (py2 - py1)) / lineLength;
            if (projection >= 0 && projection <= lineLength) {
                distance = distanceToLine;
                id = vertexID[index1 / 2];
            }
        }
    }
    return id;
}
void RouteSystem::ImportData(const std::string& filePath){
    graph = std::make_shared<WUSG::Graph<valueType>>(40000);
    WUSG::CreateGraphFromFile(filePath, *graph,true);
    citys = BuildVisualPoints(*graph);
    roads = BuildVisualRoads(*graph);
    Camera2D& camera = Camera2D::getView();
    camera.setExtent(citys->getExtent());
}
void RouteSystem::Draw(){
    if (graph == nullptr || roads == nullptr || citys == nullptr)
        return;
    roads->draw();
    citys->draw();
}
}
namespace gui {
void processWorkspace(){
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    transport::RouteSystem& system = transport::RouteSystem::getSystem();
    if (toCalcMaxDegree){
        buffer.resInfo = "最大度为" + std::to_string(WUSG::MaxDegree(*system.graph));
        toCalcMaxDegree = false;
    }
    if (toCalcSparse){
        std::stringstream iss;
        iss << "稀疏度为" << std::fixed << std::setprecision(3) << WUSG::Sparseness(*system.graph);
        buffer.resInfo = iss.str();
        toCalcSparse = false;
    }
    if (toCalcConeectCompoent){
        buffer.resInfo = "联通块数量为" + std::to_string(WUSG::CalcConnectCompoent(*system.graph));
        toCalcConeectCompoent = false;
    }
}
bool DrawPopup(){
    if (toImportData){
        ImportData();
        return true;
    }
    if (toAddPoint){
        AddPoint();
        return true;
    }
    if (toPlanRoute){
        PlanRoute();
        return true;
    }
    if (toCalcShortestPath){
        CalcShortestPath();
        return true;
    }
    return false;
}
void ImportData(){
    transport::RouteSystem& system = transport::RouteSystem::getSystem();
    static char inputBuffer[256] = "";
    ImGui::PushFont(gui::chineseFont);
    ImGui::OpenPopup("Import Data");
    ImVec2 pos = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(pos);
    if (ImGui::BeginPopup("Import Data")) {
        ImGui::Text("输入路网数据文件路径");
        ImGui::InputText("##input", inputBuffer, sizeof(inputBuffer));
        if (ImGui::Button("确认")) {
            system.ImportData(inputBuffer);
            std::cout<<system.graph->vertexCount()<<' '<<system.graph->edgeCount()<<std::endl;
            inputBuffer[0] = '\0';
            toImportData = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("取消")) {
            inputBuffer[0] = '\0';
            toImportData = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    ImGui::PopFont();
}
void AddPoint(){
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    toAddPoint = false;
}
void PlanRoute(){
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    toPlanRoute = false;
}
void CalcShortestPath(){
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    toCalcShortestPath = false;
}
}
