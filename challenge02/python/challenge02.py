import requests
import unittest

operations = { 
                "#" : lambda val : val + 1,
                "@" : lambda val : val - 1,
                "*" : lambda val : val * val,
             } 

class CompileTest(unittest.TestCase):

    def test1(self):
        self.assertEqual(compile("##*&"), "4")

    def test2(self):
        self.assertEqual(compile("&##&*&@&"), "0243")


def compile(data: str) -> str:
    result_str = ""
    result = 0
    for char in data:
        if char == "&":
            result_str += f"{result}"
        else:
            result = operations[char](result)

    return result_str


print(compile(requests.get("https://codember.dev/data/message_02.txt").text))
unittest.main()
