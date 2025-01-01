//
//  base.hpp
//  Graph_API
//
//  Created by ChanningTong on 1/1/25.
//

#ifndef base_hpp
#define base_hpp

#include <cstring>
#include <string>
namespace base {
template <typename W>
struct Vertex{
    int id;
    std::string alias;
    W x,y;
    Vertex(int id,W a,W b, std::string name = ""):id(id),x(a),y(b){
        if (name != "")
            alias = name;
        else
            alias = std::to_string(id);
    }
    Vertex():alias(""),x(W()),y(W()),id(-1){}
    bool operator==(const Vertex& rhs) const {return id == rhs.id;}
    bool operator<(const Vertex& rhs) const {return id < rhs.id;}
    bool operator>(const Vertex& rhs) const {return id > rhs.id;}
    operator std::string() const {return alias;}
    friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex){
        os << vertex.alias << " " << vertex.x << " " << vertex.y;
        return os;
    }
    Vertex& operator=(const Vertex& rhs){
        id = rhs.id;
        alias = rhs.alias;
        x = rhs.x;
        y = rhs.y;
        return *this;
    }
    Vertex(const Vertex& rhs):id(rhs.id),alias(rhs.alias),x(rhs.x),y(rhs.y){}
    explicit Vertex(int id):id(id),alias(""),x(W()),y(W()){}
};
}
#endif /* base_hpp */
