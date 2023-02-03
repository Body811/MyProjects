
from unicodedata import name
from bs4 import BeautifulSoup
import requests

search = input("Insert the item you want to search for:")


def Amazon(search):
    url = f"https://www.amazon.eg/s?k={search}&language=en"
    response = requests.get(url).text
    soup = BeautifulSoup(response, "html.parser")

    #findpage = soup.find(class_="s-pagination-strip")

    #PageNum = int(page.text[11:-4])

    target = soup.find_all(
        class_="sg-col-4-of-12 s-result-item s-asin sg-col-4-of-16 sg-col s-widget-spacing-small sg-col-4-of-20")
    for item in target:

        name = item.find(
            class_="a-size-base-plus a-color-base a-text-normal").string
        price = item.find(class_="a-price-whole")
        sublink = item.find(
            class_="a-link-normal s-underline-text s-underline-link-text s-link-style a-text-normal", href=True)
        link = "https://www.amazon.eg/" + sublink["href"]

        if price == False:
            price = "none"
            return price

        print(f"name: {name}\nprice: {price}\nlink: {link}\n")

   # for page in range( 1, PageNum+1):
    #    url = f"https://www.amazon.eg/s?k={search}&language=en&page={page}"
    #   response = requests.get(url).text
    #  soup = BeautifulSoup(response, "html.parser")
    # target = soup.find(class_="s-main-slot s-result-list s-search-results sg-row")
    # print(target.text)


Amazon(search)
