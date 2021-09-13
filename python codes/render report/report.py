from html2image import Html2Image
from datetime import date
from jinja2 import Template

data = {
    "NAME" : "Mohammad Ali",
    "PHONE_NUMBER" : "0176000000",
    "BODY_TEMP" : "101",
    "O2_LEVEL" : "95%",
    "HEART_RATE" : "65",
    "PRESCRIPTION" : "Paracitamol - napa extra",
    "now_date" : str(date.today())
}

hti = Html2Image()

f = open("./bulma_css/bulma.min.css", 'r')
css = f.read()
f.close()

f = open("./base.html", 'r')
html = f.read()
f.close()

html = Template(html).render(data)

hti.screenshot(html_str=html, css_str=css, size=(500, 705),save_as='report.png')