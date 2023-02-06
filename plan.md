# Plan

## Shapes:
@startuml

abstract class "WorldObject" {
  move();
  rotate();
  sf::Color color;
}

WorldObject --|> Shape
abstract class Shape {
  Vec3d position;
  Vec3d rotation;
}

Shape --|> Sphere
class Sphere {
  Vec3d position;
  int radius;
}

Shape --|> Cylinder
class Cylinder {
  int radius;
  int height;
}

Line <|-- WorldObject
class Line {
  Vec3d position;
  Vec3d direction;
}


Plane <|-- WorldObject
class Plane {
}

@enduml

## Shape rendering:

@startuml
class World {
  vector<WorldObject> objects;
}

class Camera {
  Vec3d position;
  Ang3d angle;
}

Renderer -- World: < uses object data 
Renderer -- Camera: < uses camera position data
Renderer - Window : > produce SFML objects

@enduml

## Input

@startuml

class Manipulator {}

class World {
  vector<WorldObject> objects;
}

class Camera {
  Vec3d position;
  Ang3d angle;
}

class InputHandler {}
Manipulator - World: processes data to modify shapes data >
Manipulator -- InputHandler: uses event data <
Manipulator -- Camera: < uses camera position data
@enduml
