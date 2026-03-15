import QtQuick
import QtQuick3D

View3D {
    anchors.fill: parent
    camera: camera

    environment: SceneEnvironment {
        clearColor: "#202020"
        backgroundMode: SceneEnvironment.Color
    }

    PerspectiveCamera {
        id: camera
        position: Qt.vector3d(0, 120, 300)
        eulerRotation.x: -20
    }

    DirectionalLight {
        eulerRotation.x: -45
        eulerRotation.y: 45
    }

    Node {
        Model {
            source: "#Cube"
            scale: Qt.vector3d(4, 0.6, 2)
            materials: DefaultMaterial {
                diffuseColor: "#303030"
            }
        }

        Node {
            id: accelerator
            position: Qt.vector3d(70, 50, -50)
            eulerRotation.x: (inputState.rightTrigger * -25) + 25

            Model {
                source: "#Cube"
                scale: Qt.vector3d(0.6, 0.3, 1.2)
                materials: DefaultMaterial {
                    diffuseColor: "#ff9933"
                }
            }
        }

        Node {
            id: brake
            position: Qt.vector3d(-15, 50, -50)
            eulerRotation.x: (inputState.leftTrigger * -25) + 25

            Model {
                source: "#Cube"
                scale: Qt.vector3d(0.6, 0.3, 1.2)
                materials: DefaultMaterial {
                    diffuseColor: "#ff9933"
                }
            }
        }

        Node {
            id: clutch
            position: Qt.vector3d(-100, 50, -50)
            eulerRotation.x: (inputState.rightStickY * -25) + 25

            Model {
                source: "#Cube"
                scale: Qt.vector3d(0.6, 0.3, 1.2)
                materials: DefaultMaterial {
                    diffuseColor: "#ff9933"
                }
            }
        }

        Node {
            id: steering
            position: Qt.vector3d(35, 70, 0)
            eulerRotation.z: inputState.rightStickY * 15

            Model {
                source: "#Cylinder"
                scale: Qt.vector3d(0.5, 0.2, 0.5)
                materials: DefaultMaterial {
                    diffuseColor: "#66ccff"
                }
            }
        }

        Node {
            id: rightStickNode
            position: Qt.vector3d(40, 35, 0)
            eulerRotation.x: -inputState.rightStickY * 15
            eulerRotation.z: inputState.rightStickX * 15

            Model {
                source: "#Cylinder"
                scale: Qt.vector3d(0.5, 0.2, 0.5)
                materials: DefaultMaterial {
                    diffuseColor: "#66ccff"
                }
            }
        }
    }
}
