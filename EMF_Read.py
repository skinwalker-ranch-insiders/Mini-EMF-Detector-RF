#!/usr/bin/env python
import datetime
import serial
import pymysql

def Add_EMF_Reading(Event_DateTime,Sensor_Value):
    from settings import db_server, db_user, db_passwd, db_name

    Sensor_ID = "EMF001"
    Conv_Sensor_Value = float(Sensor_Value)
    D_MG = Conv_Sensor_Value * 0.000166975
    conn = pymysql.connect(host=db_server,user=db_user,passwd=db_passwd,db=db_name)
    cursor = conn.cursor()
    EMF_Entry = "INSERT INTO detectors (Sensor_ID, Event_DateTime, Sensor_Value, D_MG) VALUES (%s, %s, %s, %s)"

    cursor.execute(EMF_Entry,(Sensor_ID, Event_DateTime, Sensor_Value, D_MG))
    conn.commit()
    
rx_read = 'false'

ser = serial.Serial(
        port='/dev/ttyAMA0',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)
EMFDetector = "EMF001"
EMFfile = open("/home/johns/EMF/EMF1_log.txt","a+")
avgrange = ""

while rx_read != 'true':
  avgrange=ser.readline()

  now = datetime.datetime.today()
  formatted_date = now.strftime("%Y-%m-%d %H:%M:%S")

  if avgrange != "":
    print (avgrange)
    #Add_EMF_Reading(formatted_date,avgrange)
    EMFfile.write(str(EMFDetector) + " => " + str(avgrange))
    EMFfile.write((formatted_date) + "\n")
 
EMFfile.close()
