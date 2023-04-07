#!/usr/bin/env python
import datetime
import serial
import pymysql

def Add_EMF_Reading(formatted_date,avgrange):
    from settings import db_server, db_user, db_passwd, db_name

    conn = pymysql.connect(host=db_server,user=db_user,passwd=db_passwd,db=db_name)
    cursor = conn.cursor()
    EMF_Entry = "INSERT INTO sensors (Stamp, AveRange) VALUES (%s, %s)"

    cursor.execute(Add_EMF_Reading,(Stamp, AveRange))
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

EMFfile = open("/home/johns/EMF/EMF1_log.txt","a+")

while rx_read != 'true':
        avgrange=ser.readline()

        now = datetime.datetime.today()
        formatted_date = now.strftime("%Y-%m-%d %H:%M:%S")
        
        if avgrange != "''":
            print (avgrange)
            #Add_EMF_Reading(formatted_date,avgrange)
            EMFfile.write("EMF Detector = 0001 EMF AveRange = " + str(avgrange))
            EMFfile.write((formatted_date) + "\n")
        
EMFfile.close()
