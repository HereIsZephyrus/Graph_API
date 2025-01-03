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
    if (!gui::DrawPopup()){
        camera.processKeyboard(window);
        processMouse();
    }
    if (RouteSystem::getSystem().graph != nullptr){
        gui::processWorkspace();
        BufferRecorder& buffer = BufferRecorder::getBuffer();
        if (gui::toGetBuffer && buffer.currentNode!= nullptr){
            base::Vertex<valueType> startNode = buffer.currentNode->getCity();
            double cursorX, cursorY;
            WindowParas& windowPara = WindowParas::getInstance();
            glfwGetCursorPos(windowPara.window, &cursorX, &cursorY);
            float normalX = windowPara.screen2normalX(cursorX), normalY = windowPara.screen2normalY(cursorY);
            Camera2D& camera = Camera2D::getView();
            double termX = camera.normal2worldX(normalX), termY = camera.normal2worldY(normalY);
            Primitive bufferCircle({
                Point(glm::vec3(startNode.x,startNode.y,0.0),glm::vec3(1.0,1.0,1.0)),
                Point(glm::vec3(termX,termY,0.0),glm::vec3(1.0,1.0,1.0))},GL_LINES,ShaderBucket["circle"].get());
            bufferCircle.draw();
        }
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
            if (gui::toPlanRoute)
                system.keyVertices.push_back(system.graph->getVertex(Vertex(ID)));
            else if (gui::toCalcShortestPath)
                gui::CalcShortestPath(system.graph->getVertex(Vertex(ID)));
            else if (gui::toGetBuffer){
                buffer.resInfo = "";
                gui::toGetBuffer = false;
            }
            else
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
std::vector<int> CityPoints::getBuffer(double sx,double sy,double tx, double ty){
    std::vector<int> resID;
    double sqrR = (tx - sx) * (tx - sx) + (ty - sy) * (ty - sy),windowSize = std::sqrt(sqrR) * 2;
    std::vector<size_t> res = searchWindow(sx,sy,windowSize);
    if (res.empty())
        return resID;
    for (std::vector<size_t>::iterator it = res.begin(); it != res.end(); it++){
        size_t index = *it;
        float px = vertices[index * stride],py = vertices[index * stride + 1];
        float pdis = (px - sx) * (px - sx) + (py - sy) * (py - sy);
        if (pdis < sqrR)
            resID.push_back(vertexID[index]);
    }
    return resID;
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
void Roads::remove(double x,double y,int id1,int id2){
    std::vector<size_t> res = searchWindow(x,y,10);
    for (std::vector<size_t>::iterator vLoc = res.begin(); vLoc != res.end(); vLoc++){
        size_t IDindex = (*vLoc) / 2;
        if (((vertexID[IDindex].first == id1) && (vertexID[IDindex].second == id2)) ||
            ((vertexID[IDindex].first == id2) && (vertexID[IDindex].second == id1))){
            size_t index = (*vLoc) * stride,backIndex = (vertexNum - 2) * stride;
            vertices[index] = vertices[backIndex];
            vertices[index + 1] = vertices[backIndex + 1];
            vertices[index + stride] = vertices[backIndex + stride];
            vertices[index + stride + 1] = vertices[backIndex + stride + 1];
            vertexID[IDindex] = vertexID.back();
            vertexID.pop_back();
            vertexNum-=2;
        }
    }
}
void CityPoints::remove(double x,double y,int id){
    std::vector<size_t> res = searchWindow(x,y,10);
    for (std::vector<size_t>::iterator vLoc = res.begin(); vLoc != res.end(); vLoc++)
        if (vertexID[*vLoc] == id){
            size_t index = (*vLoc) * stride,backIndex = (vertexNum - 1) * stride;
            vertices[index] = vertices[backIndex];
            vertices[index + 1] = vertices[backIndex + 1];
            vertexID[*vLoc] = vertexID.back();
            vertexID.pop_back();
            vertexNum--;
            break;
        }
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
    if (!keyVertices.isEmpty()){
        feature = nullptr;
        CreateFeature(keyVertices);
    }
    if (feature != nullptr){
        feature->draw();
        if (!gui::toPlanRoute){
            ImGui::SetNextWindowPos(ImVec2(300, 10));
            ImGui::SetNextWindowSize(ImVec2(100,80));
            ImGui::Begin("##cancel_feature", nullptr, ImGuiWindowFlags_NoResize);
            ImGui::PushFont(gui::chineseFont);
            if (ImGui::Button("取消显示",ImVec2(80, 30)))
                feature = nullptr;
            ImGui::PopFont();
            ImGui::End();
        }else{
            ImGui::Begin("##confirm_key",nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
            ImGui::SetWindowPos(ImVec2(500, 10));
            ImGui::SetWindowSize(ImVec2(60, 80));
            ImGui::PushFont(gui::chineseFont);
            if (ImGui::Button("确认"))
                gui::PlanRoute();
            ImGui::PopFont();
            ImGui::End();
        }
    }
}
void RouteSystem::CreateFeature(Vector<std::pair<base::Vertex<valueType>,base::Vertex<valueType>>>& vertices){
    std::vector<Point> vertexArray;
    if (feature != nullptr) feature = nullptr;
    for (VertexVec::iterator vertex = vertices.begin(); vertex != vertices.end(); vertex++){
        vertexArray.push_back(Point(glm::vec3(vertex->first.x,vertex->first.y,0.0),featureRoadColor));
        vertexArray.push_back(Point(glm::vec3(vertex->second.x,vertex->second.y,0.0),featureRoadColor));
    }
    feature = std::make_shared<Primitive>(vertexArray,GL_LINES,ShaderBucket["line"].get());
}
void RouteSystem::CreateFeature(Vector<base::Vertex<valueType>>& vertices){
    if (feature != nullptr) feature = nullptr;
    std::vector<Point> vertexArray;
    for (Vector<base::Vertex<valueType>>::iterator vertex = vertices.begin(); vertex != vertices.end(); vertex++)
        vertexArray.push_back(Point(glm::vec3(vertex->x,vertex->y,0.0),featureCityColor));
    feature = std::make_shared<Primitive>(vertexArray,GL_POINTS,ShaderBucket["ball"].get());
}
}
namespace gui {
void processWorkspace(){
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    transport::RouteSystem& system = transport::RouteSystem::getSystem();
    if (system.graph == nullptr)
        return;
    if (toCalcMaxDegree){
        buffer.resInfo = "最大度为" + std::to_string(WUSG::MaxDegree(*system.graph));
        toCalcMaxDegree = false;
    }
    if (toCalcSparse){
        std::stringstream iss;
        iss << "稀疏度为" << std::scientific << std::setprecision(5) << WUSG::Sparseness(*system.graph);
        buffer.resInfo = iss.str();
        toCalcSparse = false;
    }
    if (toCalcConeectCompoent){
        buffer.resInfo = "联通块数量为" + std::to_string(WUSG::CalcConnectCompoent(*system.graph));
        toCalcConeectCompoent = false;
    }
    if (toGetNeighbor){
        if (system.graph != nullptr && buffer.currentNode != nullptr){
            buffer.resInfo = WUSG::GetNeighbor(*system.graph,buffer.currentNode->getCity());
        }
        toGetNeighbor = false;
    }
    if (toDeleteObject){
        if (buffer.currentNode->isCityNode()){
            transport::Node<valueType>::CityNode city = buffer.currentNode->getCity();
            using Neighbor = typename tcb::WUSGraph<WUSG::Vertex<valueType>,valueType>::Neighbor;
            using Edge = transport::EdgeMessage;
            Neighbor neighors = system.graph->getNeighbor(city);
            std::vector<Edge> edges;
            for (Neighbor::iterator neighbor = neighors.begin(); neighbor != neighors.end(); neighbor++){
                double x = (city.x + neighbor->first.x) / 2, y = (city.y + neighbor->first.y) / 2;
                edges.push_back(Edge(x,y,VertexPair(city.id,neighbor->first.id)));
                system.roads->remove(x,y,city.id,neighbor->first.id);
            }
            system.graph->removeVertex(city);
            buffer.currentNode = nullptr;
            system.citys->remove(city.x,city.y,city.id);
            system.citys->update();
            system.roads->update();
        }
        else{
            transport::Node<valueType>::RoadNode road = buffer.currentNode->getRoad();
            system.graph->removeEdge(road.vertex1, road.vertex2);
            double x = (road.vertex1.x + road.vertex2.x) / 2, y = (road.vertex1.y + road.vertex2.y) / 2;
            buffer.currentNode = nullptr;
            system.roads->remove(x,y,road.vertex1.id,road.vertex2.id);
            system.roads->update();
        }
        toDeleteObject = false;
    }
    if (toCalcMST){
        VertexVec vertices;
        valueType totalDis = WUSG::Prim(*system.graph,vertices,buffer.currentNode->getCity());
        std::stringstream iss;
        iss << "总距离为" << std::scientific << std::setprecision(5) << totalDis;
        buffer.resInfo = iss.str();
        system.CreateFeature(vertices);
        toCalcMST = false;
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
    if (toSearchCity){
        SearchCity();
        return true;
    }
    if (toSearchRoad){
        SearchRoad();
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
    transport::RouteSystem& system = transport::RouteSystem::getSystem();
    valueType dis = WUSG::Steiner(*system.graph,system.keyVertices);
    std::stringstream iss;
    iss << "多点最短路径为" << std::fixed <<std::setprecision(3) <<dis;
    buffer.resInfo = iss.str();
    system.keyVertices.clear();
    toPlanRoute = false;
}
void CalcShortestPath(base::Vertex<valueType> termNode){
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    base::Vertex<valueType> startNode = buffer.currentNode->getCity();
    transport::RouteSystem& system = transport::RouteSystem::getSystem();
    VertexVec vertices;
    valueType dis = WUSG::ShortestPath(*system.graph, startNode, termNode,vertices);
    std::stringstream iss;
    iss << "最短路径长度为" <<std::fixed <<std::setprecision(3) <<dis;
    buffer.resInfo = iss.str();
    system.CreateFeature(vertices);
    toCalcShortestPath = false;
}
void SearchCity(){
    using Vertex = WUSG::Vertex<valueType>;
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    static char inputBuffer[256] = "";
    ImGui::PushFont(gui::chineseFont);
    ImGui::OpenPopup("Search City");
    ImVec2 pos = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(pos);
    static bool toShowFail = false;
    if (ImGui::BeginPopup("Search City")) {
        transport::RouteSystem& system = transport::RouteSystem::getSystem();
        ImGui::Text("输入待查城市编号");
        ImGui::InputText("##input", inputBuffer, sizeof(inputBuffer),ImGuiInputTextFlags_CharsDecimal);
        if (ImGui::Button("确认")) {
            int ID = std::stoi(inputBuffer);
            Vertex temp = Vertex(ID);
            Vertex take = system.graph->getVertex(temp);
            if (take!= temp){
                buffer.currentNode = std::make_shared<transport::Node<valueType>>(take);
                inputBuffer[0] = '\0';
                toSearchCity = false;
                toShowFail = false;
                Camera2D::getView().focus(take.x,take.y);
                ImGui::CloseCurrentPopup();
            }else
                toShowFail = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("取消")) {
            inputBuffer[0] = '\0';
            toSearchCity = false;
            ImGui::CloseCurrentPopup();
        }
        if (toShowFail)
            ImGui::Text("城市不存在!");
        ImGui::EndPopup();
    }
    ImGui::PopFont();
}
void SearchRoad(){
    using Vertex = WUSG::Vertex<valueType>;
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    static char inputBuffer[256] = "";
    ImGui::PushFont(gui::chineseFont);
    ImGui::OpenPopup("Search Road");
    ImVec2 pos = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(pos);
    static bool toShowFail = false;
    static Vertex selectedNeighbor = Vertex();
    if (ImGui::BeginPopup("Search Road")) {
        ImGui::Text("输入待查城市编号");
        ImGui::InputText("##input", inputBuffer, sizeof(inputBuffer));
        transport::RouteSystem& system = transport::RouteSystem::getSystem();
        if (inputBuffer[0] != '\0'){
            int currentID = std::stoi(inputBuffer);
            Vertex temp = Vertex(currentID);
            Vertex take = system.graph->getVertex(temp);
            if (take != temp){
                using Neighbor = typename tcb::WUSGraph<Vertex,valueType>::Neighbor;
                Neighbor neighbors = system.graph->getNeighbor(take);
                ImGui::BeginChild("##adding table", ImVec2(250, 200), true);
                ImGui::Text("<相邻城市列表>");
                for (Neighbor::iterator city = neighbors.begin(); city != neighbors.end(); city++){
                    bool isSelected = (selectedNeighbor == city->first);
                    std::stringstream iss;
                    iss << city->first;
                    if (ImGui::Selectable(iss.str().c_str(),isSelected)) {
                        selectedNeighbor = city->first;
                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndChild();
            }
        }
        if (ImGui::Button("确认")) {
            int ID = std::stoi(inputBuffer);
            Vertex take = system.graph->getVertex(Vertex(ID));
            if (system.graph->hasEdge(take, selectedNeighbor)){
                valueType dis = system.graph->getWeight(take, selectedNeighbor);
                buffer.currentNode = std::make_shared<transport::Node<valueType>>(take,selectedNeighbor,dis);
                inputBuffer[0] = '\0';
                toSearchRoad = false;
                toShowFail = false;
                Camera2D::getView().focus((take.x + selectedNeighbor.x)/2,(take.y + selectedNeighbor.y) / 2);
                ImGui::CloseCurrentPopup();
            }else
                toShowFail = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("取消")) {
            inputBuffer[0] = '\0';
            toSearchRoad = false;
            ImGui::CloseCurrentPopup();
        }
        if (toShowFail)
            ImGui::Text("道路不存在!");
        ImGui::EndPopup();
    }
    ImGui::PopFont();
}
void GetBuffer(double termX, double termY){
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    if (buffer.currentNode == nullptr || !buffer.currentNode->isCityNode())
        return;
    transport::RouteSystem& system = transport::RouteSystem::getSystem();
    base::Vertex<valueType> startNode = buffer.currentNode->getCity();
    std::vector<int> cityInBuffer = system.citys->getBuffer(startNode.x, startNode.y, termX, termY);
    Vector<base::Vertex<valueType>> vertices;
    std::stringstream iss;
    iss<<"<相邻城市列表>"<<'\n'<<std::fixed<<std::setprecision(3);
    for (std::vector<int>::iterator cityID = cityInBuffer.begin(); cityID != cityInBuffer.end(); cityID++){
        base::Vertex<valueType> orientCity = system.graph->getVertex(base::Vertex<valueType>(*cityID));
        vertices.push_back(orientCity);
        double dis = std::sqrt((startNode.x - orientCity.x) * (startNode.x - orientCity.x) + (startNode.y - orientCity.y) * (startNode.y - orientCity.y));
        iss<<orientCity<<"距离为"<<dis<<'\n';
    }
    buffer.resInfo = iss.str();
    system.CreateFeature(vertices);
}
}
