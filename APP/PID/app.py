import webview
import xml.etree.ElementTree as ET
import urllib.parse
import re
import json
import os
import time


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
            f"&limit=15&title={title_encoded}&subtitle={subtitle_encoded}&minutesBefore=0"    #in future add &format=time
        )
        return url
    def open_tablo(self, url):
      
        w = webview.create_window("PID Tablo", url, zoomable=True)

       


html_file = os.path.join(os.path.dirname(__file__), "index.html")
with open(html_file, "r", encoding="utf-8") as f:
    html_content = f.read()


if __name__ == '__main__':

    print("app running!!! Do not close this window!!")
    print("WARNING: This is not oficial aplication provided by PID (Pražská Integrovaná Doprava)")
    window = webview.create_window("PID Web Console", html=html_content, js_api=API())

    webview.start()
    print("app termination signal received! Please wait, this window will be closed automatically")
    time.sleep(3)
  
