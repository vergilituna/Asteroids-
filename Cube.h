class Cube{
 private:
  float x;
  float y;
  float z;
  float rotx;
  float roty;
  float rotz;
  
 public:
  Cube();
  Cube(float xx, float yy, float zz, float rx=0, float ry=0, float rz=0);
  void draw();
  void move();
};
