#!/usr/bin/python

import os
import sys
from lxml import etree as ET
from xml.dom import minidom
from subprocess import call
import argparse

scriptPath=os.path.dirname(os.path.realpath(sys.argv[0]))

parser = argparse.ArgumentParser(description='Create a settings file for the CAENdaq software')
parser.add_argument('-f','--filename', help='The output filename. If the file exists, it will be overwritten', default='DEFAULT.xml', required=True)


defaultTree = ET.parse(scriptPath+"/Settings.xml")

defaultRoot = defaultTree.getroot()

for active in defaultRoot:
     for param in active:          
          p = default=str(param.text).strip()
          parser.add_argument('--'+param.tag, default=p, help = "(default: %(default)s)")

args = parser.parse_args()


fname = args.filename
del args.filename

root = ET.Element("Active")

for arg in vars(args):
     ET.SubElement(root, arg).text = '\n    '+str(getattr(args, arg))+'\n  '

f = open(str(fname), 'w')

f.write("<xml>\n")

f.write(ET.tostring(root, pretty_print=True))
f.write("</xml>")




