import requests
import json
value={
  # "vc_type": "Car",
  # "vc_number": "MH31AV7274",
  # "vc_colour": "white",
  # "vc_date": "27/09/2022",
  # "vc_time":"4/30/15",
  # "vc_model":"Swift"
  
  
 	"id": "56",
    "name":"Swara",
 	"title": "Testing at Mantra",
 	"completed": "True"
  }
#192.168.5.193
jsonStr=json.dumps(value, indent=4)
# r = requests.post('http://127.0.0.1:5000/emp',json=jsonStr)
r = requests.get('http://127.0.0.1:5000/empdb/employee/101')
print(r)
print(f"Status Code: {r.status_code}, Response: {r.json()}")

# import requests
# from requests.structures import CaseInsensitiveDict
# import asyncio
# import httpx
# import nest_asyncio

# nest_asyncio.apply()

# async def main():
#     async with httpx.AsyncClient() as client:
#         url = "http://demofacesvc.mantratecapp.com/api/DeviceCommunication/SuccessTransaction"
#         data3={"cardType": 3,
#        	"detectedTemperature": 0.0,
#        	"deviceUniqueId": "MSDIFR001",
#        	"employeeId": 230,
#        	"employeeUniqueId": "MN001150",
#        	"faceThreshold": 0.0, #face matching threasold (score) at punch time
#        	"inOutTime": "2022-10-31 19:43:11",
#        	"isCovered": 0, #Mask or without mask
#        	"mode": "Default",
#        	"photo": "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",
#        	"punchMatchType": 2}
#         response = await client.post(url, data=data3)
#         print(response.status_code)
#         print(response.text)
# loop = asyncio.get_event_loop()
# loop.run_until_complete(main())


# url="http://demofacesvc.mantratecapp.com/api/DeviceCommunication/SayHello"
# #url=""
# #url = "http://192.168.5.193:8080/Example/getface"
# url2 = "http://demofacesvc.mantratecapp.com/api/DeviceCommunication/GetByEmployeeUniqueId"

# url3="http://demofacesvc.mantratecapp.com/api/DeviceCommunication/SuccessTransaction"

# headers = CaseInsensitiveDict()
# headers["Accept"] = "application/json"
# headers["Content-Type"] = "application/json"

# # data = '{"id": "126","count":2,"date": "02-03-2023","time": "16:29:20"}'
# data={"appVersion": "1.86.3",
# 	"deviceTime": "2023-08-09 16:35:13",
# 	"deviceType": "M1",
# 	"deviceUniqueId": "MSDIFR001",
# 	"mac": "d8:5e:d3:93:01:15",
# 	"transactionCount": 0,
# 	"userCount": 3}

# data2={"cardNo": "", #Not mandatory
# 	"cardType": 0, #Not mandatory
# 	"deviceUniqueId": "MSDIFR001",
# 	"employeeUniqueId": "mn001150"}
 
# data3={"cardType": 3,
# 	"detectedTemperature": 0.0,
# 	"deviceUniqueId": "MSDIFR001",
# 	"employeeId": 230,
# 	"employeeUniqueId": "MN001150",
# 	"faceThreshold": 0.0, #face matching threasold (score) at punch time
# 	"inOutTime": "2022-10-31 19:43:11",
# 	"isCovered": 0, #Mask or without mask
# 	"mode": "Default",
# 	"photo": "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",
# 	"punchMatchType": 2}
# # data='{"count":4}'
# # resp = requests.post(url2, headers=headers, data=data)

# # print(resp.status_code)
 
# dat=requests.post(url,headers=headers,json=data)
# print(dat.json())
# recieved_data=dat.json()
# print(recieved_data['serDateTime'])

# #dat=requests.get(url)
# dat2=requests.post(url2,headers=headers,json=data2)
# print(dat2.json())
# recieved_data2=dat2.json()
# photo=recieved_data2['photo']
# employeeId=recieved_data2['employeeId']


# data3['photo']=photo
# data3['employeeId']=employeeId
# dat3=requests.post(url3,headers=headers,json=data3)

# print(dat3.json())


