import requests
from bs4 import BeautifulSoup
import json

# Puts the URL into a string variable and passes that into the get() function from the requests object
# Puts the result of that into 'response'
url = "https://ctxt.io/2/AAC4CPsSFg"
response = requests.get(url)

# Uses the BS webscraper; the text attribute contains the html --> this is passed to the BS constructor
# Also, the type of parser to use is passed (this is an in built one ? in python lib)
soup = BeautifulSoup(response.text, 'html.parser')

# Uses a BS method to get the parsed text, and this is put into a new variable
text_content = soup.get_text()

# Splits the lines up into a list of lines
lines = text_content.splitlines()

cleaned_lines = [line for line in lines if ' ' not in line]
lines_final = [line for line in cleaned_lines if len(line)>0]

print(lines_final)


with open('day1_lines_v2.json', 'w') as json_file:
    json.dump(lines_final, json_file, indent=4)

    
