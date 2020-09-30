import QtQuick 2.4
import QtCharts 2.3

Item {
    id: element
    width: 610
    height: 380
    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 700
        height: 500
        gradient: Gradient {
                GradientStop { position: 0.0; color: "#056087" }
                GradientStop { position: 1.0; color: "#0b1324" }
            }

    }

    Text {
        id: elSweepGasFlow
        x: 15
        y: 41
        width: 166
        height: 29
        color:"#ffffff"
        text: "Sweep Gas Flow"
        font.pixelSize: 18
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        textFormat: Text.AutoText
    }

    TextInput {
        id: elSweepGasFlowDat
        x: 36
        y: 76
        width: 124
        height: 81
        text: (SweepGasData.lastReadingSweepGas.y).toString();
        color:"#a0cf6b"
        font.weight: Font.DemiBold
        font.family: "Helvetica"
        font.pointSize: 30
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter


    }

    Text {
        id: elCO2Removal
        x: 15
        y: 187
        width: 166
        height: 32
        color:"#ffffff"
        text: qsTr("CO2 Removal")
        anchors.left: elSweepGasFlow.left
        anchors.right: elSweepGasFlow.right
        font.pixelSize: 18
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.horizontalCenter: elSweepGasFlow.horizontalCenter
    }

    TextInput {
        id: elCO2RemovalData
        x: 43
        y: 239
        text: (CO2Data.lastReadingCO2.y).toString();
        font.weight: Font.DemiBold
        width: 124
        height: 81
        color:"#00cd00"
        font.family: "Helvetica"
        font.pointSize: 30
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
}

    ChartView {
       // id: lineGas
        x: 204
        y: 0
        width: 436
        height: 380
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        antialiasing: true

        title: "Dashboard"
        theme: ChartView.ChartThemeBlueCerulean

        ValueAxis {
            id: timeAxis

        }

        ValueAxis {
            id:sweepGasAxis
            min: 100
            max: 2000
        }
        ValueAxis {
            id:co2Axis
            min: 100
            max: 1000
        }
        LineSeries {
            id: sweepGasSeries
            name: "Sweep Gas Flow"
            axisX: timeAxis
            axisY: sweepGasAxis      
        }


        Connections {
            target:SweepGasData
           // onNewReading:{
            function onNewReadingSweepGas() {

                if (sweepGasSeries.count > 10)
                        sweepGasSeries.remove(0);
                console.log(SweepGasData.lastReadingSweepGas.x);
                console.log(SweepGasData.lastReadingSweepGas.y);
                sweepGasSeries.append(SweepGasData.lastReadingSweepGas.x, SweepGasData.lastReadingSweepGas.y)
                console.log("SweepGasData");
                console.log(sweepGasSeries);

                // adjust time axis
                timeAxis.min = sweepGasSeries.at(0).x
                timeAxis.max = sweepGasSeries.at(sweepGasSeries.count -1).x


                // adjust sweepGas axis
                if (SweepGasData.lastReadingSweepGas.y < sweepGasAxis.min)
                    sweepGasAxis.min = SweepGasData.lastReadingSweepGas.y;
                console.log("SweepGasData.lastReadingSweepGas.y");
                console.log(SweepGasData.lastReadingSweepGas.y);
                if (SweepGasData.lastReadingSweepGas.y >sweepGasAxis.max)
                    sweepGasAxis.max = SweepGasData.lastReadingSweepGas.y;
                console.log(sweepGasAxis.max);
            }
        }


        LineSeries {
                   id: co2Series
                   name:"CO2"
                   axisX: timeAxis



               Connections {
                   target:CO2Data
                  // onNewReading:{
                   function onNewReadingCO2() {
                       console.log("lastReadingCO2");
                       console.log(CO2Data.lastReadingCO2.y);

                       if (co2Series.count > 10)
                               co2Series.remove(0);

                       co2Series.append(CO2Data.lastReadingCO2.x, CO2Data.lastReadingCO2.y)
                       console.log("CO2Data.lastReadingCO2.y");
                       console.log(CO2Data.lastReadingCO2.y);

                       // adjust time axis
                       timeAxis.min = co2Series.at(0).x;
                       timeAxis.max = co2Series.at(co2Series.count -1).x;


                       // adjust CO2 axis
                       if (CO2Data.lastReadingCO2.y < co2Axis.min)
                           co2Axis.min = CO2Data.lastReadingCO2.y;
                        console.log(CO2Data.lastReadingCO2.y)
                       if (CO2Data.lastReadingCO2.y > co2Axis.max)
                           co2Axis.max = CO2Data.lastReadingCO2.y;
                        console.log(co2Axis.max);
                   }  }
               }
           }

    }
