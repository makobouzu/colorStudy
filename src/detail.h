//
//  detail.h
//  ColorStudy_day4
//
//  Created by Makoto Amano on 2020/02/17.
//

#ifndef detail_h
#define detail_h

using VertexColorPair = std::pair<glm::vec3, ofColor>;

namespace calculation {
namespace detail {
inline bool comparePair(const std::pair<glm::vec3, float>& a, const std::pair<glm::vec3, float>& b) {
    if(a.second != b.second){
        return a.second < b.second;
    }
}

inline ofColor findColor(const std::vector<VertexColorPair>& vertex, const glm::vec3& pos){
    ofColor color;
    auto findPos = std::find_if(vertex.begin(), vertex.end(), [&pos](const VertexColorPair& element){ return element.first == pos;});
    color = (*findPos).second;
    return color;
}

inline float distance(const glm::vec3& pos1, const glm::vec3& pos2){
    float distance;
    distance = sqrt(pow(pos2.x - pos1.x, 2.0) + pow(pos2.y - pos1.y, 2.0) + pow(pos2.z - pos1.z, 2.0));
    return distance;
}

inline bool dividingPoint(const glm::vec3& intersection, const glm::vec3& pos1, const glm::vec3& pos2){
    float distance = detail::distance(pos1, pos2);
    float pos1Tointer = detail::distance(pos1, intersection);
    float pos2Tointer = detail::distance(pos2, intersection);
    float ratio1 = pos1Tointer / distance;
    float ratio2 = pos2Tointer / distance;
    
    if(int(distance) == int(pos1Tointer+pos2Tointer)){
        //intersectionは内分点
        return true;
    }else{
        //intersectionは外分点
        return false;
    }
}

}

//--------------------------------------------------------------

inline glm::vec3 emphasisPos(const std::vector<VertexColorPair>& vertex){
    glm::vec3 sum, emphasis;
    for(auto i = 0; i != vertex.size(); ++i){
        sum += vertex.at(i).first;
    }
    emphasis = sum / vertex.size();
    return emphasis;
}

inline ofColor emphasisCol(const std::vector<VertexColorPair>& vertex){
    ofColor sum, emphasisCol;
    for(auto i = 0; i != vertex.size(); ++i){
        sum += vertex.at(i).second;
    }
    emphasisCol = sum / vertex.size();
    return emphasisCol;
}

//output nearest 2 vertex
inline std::vector<glm::vec3> neighborVertex(const glm::vec3& target, const std::vector<VertexColorPair>& vertex, int num){
    std::vector<std::pair<glm::vec3, float>> vertexDistance;
    
    for(auto i = 0; i < vertex.size(); ++i){
        float tar2pos = sqrt(pow(target.x - vertex.at(i).first.x, 2.0) + pow(target.y - vertex.at(i).first.y, 2.0) + pow(target.z - vertex.at(i).first.z, 2.0));
        vertexDistance.push_back(std::make_pair(vertex.at(i).first, tar2pos));
    }
    
    std::sort(vertexDistance.begin(), vertexDistance.end(), detail::comparePair);
    
    std::vector<glm::vec3> neighbor;
    int size = int(vertexDistance.size())-num;
    for(auto i = 0; i < size; ++i){
        vertexDistance.pop_back();
    }
    for(auto&& v : vertexDistance){
        neighbor.push_back(v.first);
    }
    return neighbor;
}

inline glm::vec3 polygonIntersection(const glm::vec3& target, const std::vector<glm::vec3>& neighbor, const glm::vec3& emphasis){
    glm::vec3 pos1, pos2;
    pos1  = neighbor.at(0);
    pos2  = neighbor.at(1);
    
    glm::vec3 intersection;
    
//  y = ax + b or y = b
    float a, b;
    if(pos1.x != pos2.x){
        a = (pos2.y - pos1.y)/(pos2.x - pos1.x);
        b = -1*(pos2.y - pos1.y)/(pos2.x - pos1.x) * pos1.x + pos1.y;
    }else{
        a = pos2.y - pos1.y;
        b = -1*(pos2.y - pos1.y) * pos1.x + pos1.y;
    }
        
//  y = cx + d
    float c, d;
    if(target.x != emphasis.x){
        c = (target.y - emphasis.y)/(target.x - emphasis.x);
        d = -1*(target.y - emphasis.y)/(target.x - emphasis.x) * emphasis.x + emphasis.y;
    }else{
        c = (target.y - emphasis.y);
        d = -1*(target.y - emphasis.y) * emphasis.x + emphasis.y;
    }
    
    
        intersection.x = (d - b)/(a - c);
        intersection.y = (a*d - b*c)/(a - c);
        intersection.z = pos1.z;

    if(detail::dividingPoint(intersection, pos1, pos2)){
        return intersection;
    }else{
        pos1  = neighbor.at(0);
        pos2  = neighbor.at(2);

        //  y = ax + b or y = b
        float a, b;
        if(pos1.x != pos2.x){
            a = (pos2.y - pos1.y)/(pos2.x - pos1.x);
            b = -1*(pos2.y - pos1.y)/(pos2.x - pos1.x) * pos1.x + pos1.y;
        }else{
            a = pos2.y - pos1.y;
            b = -1*(pos2.y - pos1.y) * pos1.x + pos1.y;
        }

        //  y = cx + d
        float c, d;
        if(target.x != emphasis.x){
            c = (target.y - emphasis.y)/(target.x - emphasis.x);
            d = -1*(target.y - emphasis.y)/(target.x - emphasis.x) * emphasis.x + emphasis.y;
        }else{
            c = (target.y - emphasis.y);
            d = -1*(target.y - emphasis.y) * emphasis.x + emphasis.y;
        }

        intersection.x = (d - b)/(a - c);
        intersection.y = (a*d - b*c)/(a - c);
        intersection.z = pos1.z;
        return intersection;
    }
}

inline ofColor intersectionColor(const glm::vec3& intersection, const std::vector<VertexColorPair>& vertex, const std::vector<glm::vec3>& neighbor){
    glm::vec3 pos1, pos2;
    pos1  = neighbor.at(0);
    pos2  = neighbor.at(1);
    
    ofColor pos1Col = detail::findColor(vertex, pos1);
    ofColor pos2Col = detail::findColor(vertex, pos2);
    
    ofColor color;
    float disLine = detail::distance(pos1, pos2);
    float pos1inter = detail::distance(intersection, pos1);
    float ratio = pos1inter / disLine;
    
    if(ratio > 1){
        color = pos2Col;
    }else{
        color = pos1Col.getLerped(pos2Col, ratio);
    }
    
    return color;
}

inline ofColor targetColor(const glm::vec3& target, const glm::vec3& intersection, const ofColor& interCol, const glm::vec3& point, const ofColor pointCol){
    
    ofColor color;
    float distance = detail::distance(point, intersection);
    float point2target = detail::distance(target, point);
    float ratio = point2target / distance;
    
    if(ratio > 1){
        color = interCol;
    }else{
        color = pointCol.getLerped(interCol, ratio);
    }
    return color;
}

}//namespace Calculation

#endif /* detail_h */
