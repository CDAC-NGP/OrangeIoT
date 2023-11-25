from flask import Flask
from flask import jsonify
from flask import request

app = Flask(__name__)

iotData=[ 
     {'id':'o101',
     'Sensor': {'RFID':'11002480000','AnalogPin 1': '1024','AnalogPin 2': '1024','DigitalIn 1': 'High','DigitalIn 2': 'Low'},
     'Actuator': {'Servo 1':'180','Servo 2':'180','Digital Out 1':'0','Digital Out 2':'0'}
     },
     
     {'id':'o102',
     'Sensor': {'RFID':'11002487487','AnalogPin 1': '1024','AnalogPin 2': '1024','DigitalIn 1': 'High','DigitalIn 2': 'Low'},
     'Actuator': {'Servo 1':'180','Servo 2':'180','Digital Out 1':'High','Digital Out 2':'High'}
     },
     
     {'id':'o103',
     'Sensor': {'RFID':'11002487488','AnalogPin 1': '1024','AnalogPin 2': '1024','DigitalIn 1': 'High','DigitalIn 2': 'Low'},
     'Actuator': {'Servo 1':'180','Servo 2':'180','Digital Out 1':'High','Digital Out 2':'High'}
     } 
]

print("Server")
# 'http://192.168.29.229:5000/senData?id=o102&rfd=202303&a1=150&a2=1020&di1=1&di2=1';

@app.route('/senData',methods=['GET'])
def senData():
    nodeId = request.args['id']
    RFID = request.args['rfd']
    Analog1 = request.args['a1']
    Analog2 = request.args['a2']
    Digital1 = request.args['di1']
    Digital2 = request.args['di2']
    # print(nodeId,RFID,Analog1,Analog2,Digital1,Digital2)
    
    ###/******Update the Sensor Values ****/###    
    for i in range(len(iotData)):
        if iotData[i]['id']==nodeId:
            iotData[i]['Sensor']['RFID']  = RFID
            iotData[i]['Sensor']['AnalogPin 1']  = Analog1
            iotData[i]['Sensor']['AnalogPin 2']  = Analog2
            iotData[i]['Sensor']['DigitalIn 1']  = Digital1
            iotData[i]['Sensor']['DigitalIn 2']  = Digital2
            
            response = jsonify({'allData':iotData[i]['Actuator']})
            response.headers.add('Access-Control-Allow-Origin', '*')
            
            print(i,nodeId,RFID)
            break

   
    return response

@app.route('/actData',methods=['GET'])
def actData():
    nodeId = request.args['id']
    Servo1 = request.args['s1']
    Servo2 = request.args['s2']
    dOut1 = request.args['do1']
    dOut2 = request.args['do2']
    # print(nodeId,Servo1,Servo2,dOut1,dOut2)
    
    for i in range(len(iotData)):
        if iotData[i]['id']==nodeId:
            iotData[i]['Actuator']['Servo 1']  = Servo1
            iotData[i]['Actuator']['Servo 2']  = Servo2
            iotData[i]['Actuator']['Digital Out 1']  = dOut1
            iotData[i]['Actuator']['Digital Out 2']  = dOut2
    
    
            response = jsonify({'allData':iotData[i]['Sensor']})
            response.headers.add('Access-Control-Allow-Origin', '*')
    return response



# @app.route('/user')
# name = request.args['name']
# age = request.args.get('age', default='N/A')

if __name__ == '__main__':
    app.run(host='0.0.0.0')