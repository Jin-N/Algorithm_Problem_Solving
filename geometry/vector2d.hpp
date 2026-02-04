
template<class T>
struct vector2d{
    T x, y;

    vector2d() : x(0), y(0) {}
    vector2d(T _x, T _y) : x(_x), y(_y) {}

    bool operator == (const vector2d& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    auto cross(const vector2d& rhs) const {
        return x * rhs.y - rhs.x * y;
    }
};

//각도의 대소 비교. (1, 0)과 (0, 0)의 각도는 0이며, 반시계 방향으로 증가한다.
template<class T>
bool hasBiggerAngle(const vector2d<T>& p, const vector2d<T>& q){
    if (p.y >= 0 && q.y < 0) return false;
    if (p.y < 0 && q.y >= 0) return true;
    auto temp = q.cross(p);
    if (temp) return temp > 0;
    // 외적이 0이면서 true를 반환하는 유일한경우.(사이각은 180도)
    if (p.x < 0 && q.x >= 0) return true;
    // 외적이 0인 나머지 경우는 사이각이 0이거나 
    // p, q가 각각 0도, 180도인 경우다.
    return false; 
}