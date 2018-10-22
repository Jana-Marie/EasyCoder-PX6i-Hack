#!/usr/bin/python

import cups
import os, sys

dirname, filename = os.path.split(os.path.abspath(sys.argv[0]))

conn = cups.Connection()
printers = conn.getPrinters()

for printer in printers:
	print(printer, printers[printer]["device-uri"])

fileName = os.path.join(dirname,"otter.txt")
print(fileName)
conn.printFile('Thermal_Label_Printer_Intermec_EasyCoder_PX6i', fileName, " ", {'media':'Aufkleber Flohmarkt Klein'})
