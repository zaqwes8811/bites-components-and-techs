import QtQuick 1.0
Rectangle {
    id: screen
    color: "#545454"
     width: 300; height: 300
	Image{
             id: arrowIcon
             source: "png.png"
             anchors.horizontalCenter: parent.horizontalCenter
         }
	

     Rectangle {
     width: 100; height: 100
     color: "blue"
     transform: Rotation { origin.x: 75; origin.y: 75; angle: 45}
 }
 Row {
     x: 10; y: 10
     spacing: 10

     Image { source: "png.png" }
     Image {
         source: "png.png"
         transform: Rotation { origin.x: 30; origin.y: 30; axis { x: 0; y: 1; z: 0 } angle: 18 }
         smooth: true
     }
     Image {
         source: "png.png"
         transform: Rotation { origin.x: 30; origin.y: 30; axis { x: 0; y: 1; z: 0 } angle: 36 }
         smooth: true
     }
     Image {
         source: "png.png"
         transform: Rotation { origin.x: 30; origin.y: 30; axis { x: 0; y: 1; z: 0 } angle: 54 }
         smooth: true
     }
     Image {
         source: "png.png"
         transform: Rotation { origin.x: 30; origin.y: 30; axis { x: 0; y: 1; z: 0 } angle: 72 }
         smooth: true
     }
 }
 Item {
     width: 300; height: 300

     Rectangle {
         id: rect
         width: 50; height: 50
         color: "red"

         Behavior on x { SpringAnimation { spring: 2; damping: 0.2 } }
         Behavior on y { SpringAnimation { spring: 2; damping: 0.2 } }
     }

     MouseArea {
         anchors.fill: parent
         onClicked: {
             rect.x = mouse.x - rect.width/2
             rect.y = mouse.y - rect.height/2
         }
     }
 }
}
 
