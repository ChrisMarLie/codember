import requests
import unittest

class FindPatternsTest(unittest.TestCase):

    def test1(self):
        self.assertEqual(find_patterns("keys house HOUSE house keys"), "keys2house3")

    def test2(self):
        self.assertEqual(find_patterns("cup te a cup"), "cup2te1a1")

    def test3(self):
        self.assertEqual(find_patterns("houses house housess"), "houses1house1housess1")


def find_patterns(data: str) -> str:
    word_list = data.lower().strip().split()
    return "".join((f"{word}{repeated}" for word, repeated in {word: word_list.count(word) for word in word_list}.items()))


print(find_patterns(requests.get("https://codember.dev/data/message_01.txt").text))
unittest.main()
