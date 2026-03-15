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
        Node {
            id: rightTrigger
            position: Qt.vector3d(70, 50, -50)
            eulerRotation.x: (inputState.rightTrigger * -25)  - 45

            Model {
                source: "#Cube"
                scale: Qt.vector3d(0.6, 0.3, 1.2)
                materials: DefaultMaterial {
                    diffuseColor: {
                        if (inputState.rightTrigger < 0.05)
                            return "#66ccff"
                        if (inputState.rightTrigger < 0.15)
                            return "#ffd54a"
                        return "#ff5533"
                    }
                }
            }
        }

        Node {
            id: leftTrigger
            position: Qt.vector3d(-70, 50, -50)
            eulerRotation.x: (inputState.leftTrigger * -25) - 45

            Model {
                source: "#Cube"
                scale: Qt.vector3d(0.6, 0.3, 1.2)
                materials: DefaultMaterial {
                    diffuseColor: {
                        if (inputState.leftTrigger < 0.05)
                            return "#66ccff"
                        if (inputState.leftTrigger < 0.15)
                            return "#ffd54a"
                        return "#ff5533"
                    }
                }
            }
        }

        Node {
            id: rightStick
            position: Qt.vector3d(70, 0, 0)
            eulerRotation.z: (-inputState.rightStickX * 25)
            eulerRotation.x: (-inputState.rightStickY * 25)

            Model {
                source: "#Cylinder"
                scale: Qt.vector3d(0.6, 0.3, 1.2)
                materials: DefaultMaterial {
                    diffuseColor: {
                        let mag = inputState.rightStickMagnitude
                        if (mag < 0.05)
                            return "#66ccff"
                        if (mag < 0.15)
                            return "#ffd54a"
                        return "#ff5533"
                    }
                }
            }
        }

        Node {
            id: leftStick
            position: Qt.vector3d(-70, 0, 0)
            eulerRotation.z: (-inputState.leftStickX * 25)
            eulerRotation.x: (-inputState.leftStickY * 25)

            Model {
                source: "#Cylinder"
                scale: Qt.vector3d(0.6, 0.3, 1.2)
                materials: DefaultMaterial {
                    diffuseColor: {
                        let mag = inputState.leftStickMagnitude
                        if (mag < 0.05)
                            return "#66ccff"
                        if (mag < 0.15)
                            return "#ffd54a"
                        return "#ff5533"
                    }
                }
            }
        }
    }

}
