#ifndef ZPOINT_H
#define ZPOINT_H
class  point3f{
   public:
    float x;
    float y;
    float z;

   public:
        point3f(float xIn,float yIn,float zIn):x(xIn),y(yIn),z(zIn)
        {
        }
        point3f():x(0.0f),y(0.0f),z(0.0f){

        }
        ~point3f(){}
        inline void operator+= ( const point3f& V2 )
        {
        x += V2.x;
        y += V2.y;
        z += V2.z;
        }
        inline void operator-= ( const point3f& V2 )
        {
        x -= V2.x;
        y -= V2.y;
        z -= V2.z;
        }
        inline float operator[] ( int i )
        {
            if ( i == 0 ) return x;
            else if ( i == 1 ) return y;
            else return z;
        }
        inline point3f& operator=(const point3f& other)
        {
            if(&other!=this)
            {
                this->x = other.x;
                this->y = other.y;
                this->z = other.z;
            }
            return *this;
        }



};
#endif // ZPOINT_H
