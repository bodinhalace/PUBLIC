import webview
import xml.etree.ElementTree as ET
import urllib.parse
import re
import json
import os
import time
from rich.console import Console                     #TUI 
from rich.table import Table                         #TUI LIB
from rich.panel import Panel                         #TUI LIB
from rich import print as rp  

console = Console(style="green1 on black")
console2 = Console(style="red on black")
tree = ET.parse("StopsByName.xml")
root = tree.getroot()

rows = []
for group in root.findall("group"):
    for stop in group.findall("stop"):
        gtfs = stop.get("gtfsIds", "").strip()
        alt_name = stop.get("altIdosName", "").strip()
        platform = stop.get("platform", "").strip()
        for line in stop.findall("line"):
            name = line.get("name", "").strip()
            direction = line.get("direction", "").strip()
            rows.append([name, alt_name, direction, gtfs, platform])



class API:
    def search(self, mode, query):
        query = query.lower()

        if mode == "fulltext":
            filtered = [r for r in rows if any(query in c.lower() for c in r)]

        elif mode in ["name", "alt", "direction", "gtfs", "platform"]:
            idx = {"name":0,"alt":1,"direction":2,"gtfs":3,"platform":4}[mode]
            filtered = [r for r in rows if query in r[idx].lower()]

        elif mode == "regex":
            regex = re.compile(query, re.IGNORECASE)
            filtered = [r for r in rows if any(regex.search(c) for c in r)]

        else:
            filtered = []

        return filtered

    def build_url(self, gtfs_list, title, subtitle):
        ids_encoded = urllib.parse.quote(";".join(gtfs_list))
        title_encoded = urllib.parse.quote(title)
        subtitle_encoded = urllib.parse.quote(subtitle)

        url = (
            f"https://data.pid.cz/departures/?ids={ids_encoded}"
            f"&limit=15&title={title_encoded}&subtitle={subtitle_encoded}&minutesBefore=0"    
        )
        return url
        
        
    def build_url_time(self, gtfs_list, title, subtitle):
        ids_encoded = urllib.parse.quote(";".join(gtfs_list))
        title_encoded = urllib.parse.quote(title)
        subtitle_encoded = urllib.parse.quote(subtitle)

        url2 = (
            f"https://data.pid.cz/departures/?ids={ids_encoded}"
            f"&limit=15&title={title_encoded}&subtitle={subtitle_encoded}&minutesBefore=0&format=time"    
        )
        return url2
        
    def open_tablo(self, url):
      
        w = webview.create_window("PID Tablo", url, zoomable=True)
    def open_tablo_2(self, url2):
      
        w = webview.create_window("PID Tablo (time&delay)", url2, zoomable=True)    

       


html_file = os.path.join(os.path.dirname(__file__), "index.html")
with open(html_file, "r", encoding="utf-8") as f:
    html_content = f.read()


if __name__ == '__main__':
    os.system("cls")
    os.system("color 0a")
    console.print(Panel("AUTOR: bodinhalace \nVERSION: 1.2\napp running!!! Do not close this window!!\nWARNING: This is not oficial aplication provided by PID (Pražská Integrovaná Doprava)"))
   # print("app running!!! Do not close this window!!")
   # print("WARNING: This is not oficial aplication provided by PID (Pražská Integrovaná Doprava)")
    window = webview.create_window("PID Web Console", html=html_content, js_api=API(), width=1024, height=530)

    webview.start(icon='app.ico')
    os.system("cls")
    os.system("color 04")
    console2.print(Panel("[red]app termination signal received! Please wait, this window will be closed automatically[/red]"))
    time.sleep(3)
    os.system("cls")
    os.system("color 0f")
  
