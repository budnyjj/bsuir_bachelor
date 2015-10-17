#!/usr/bin/env python

import argparse
import sys


class TextProcessorCmdInterface:
    HELP_USAGE =\
'''text_processor <command> [<args>]

The possible commands are:
    count
    intersection
    length
    repeats
    replace
    reverse
    substring
'''

    def __init__(self, processor):
        self._text_processor = processor
        _arg_parser = argparse.ArgumentParser(
            description = 'Collection of text-processing functions',
            usage = self.HELP_USAGE,
        )

        _arg_parser.add_argument('command', help='Subcommand to run')

        args = _arg_parser.parse_args(sys.argv[1:2])
        if not hasattr(self, args.command):
            print('Unrecognized command')
            _arg_parser.print_help()
            exit(1)

        getattr(self, args.command)()

    def substring(self):
        _arg_parser = argparse.ArgumentParser(
            description='Print substring with specified parameters'
        )

        _arg_parser.add_argument('--start', type=int, default=0,
                                 help='Start index')
        _arg_parser.add_argument('--length', type=int,
                                 help='Length')
        _arg_parser.add_argument('string', type=str,
                                 help='Source string')

        args = _arg_parser.parse_args(sys.argv[2:])

        print('Execute substring command with following arguments:\n'\
              '  string: {}, start: {}, length: {}'.format(
            args.string, args.start, args.length
        ))

        print('Result is:', self._text_processor.substring(
            args.string, args.start, args.length
        ))

    def count(self):
        _arg_parser = argparse.ArgumentParser(
            description='Count number of occurences of specified word in text'
        )

        _arg_parser.add_argument('--target', type=str, default='',
                                 help='Target word')
        _arg_parser.add_argument('string', type=str,
                                 help='Source string')

        args = _arg_parser.parse_args(sys.argv[2:])

        print('Execute count command with following arguments:\n'\
              '  string: {}, target: {}'.format(
            args.string, args.target
        ))

        print('Result is:', self._text_processor.count(
            args.string, args.target
        ))

    def repeats(self):
        _arg_parser = argparse.ArgumentParser(
            description='Find all word repeats in text'
        )

        _arg_parser.add_argument('string', type=str,
                                 help='Source string')

        args = _arg_parser.parse_args(sys.argv[2:])

        print('Execute repeats command with following arguments:\n'\
              '  string: {}'.format(args.string))

        print('Result is:')
        for w, r in self._text_processor.repeats(args.string).items():
            print('  {}: {}'.format(w, r))

    def replace(self):
        _arg_parser = argparse.ArgumentParser(
            description='Replace all occurences of specified word in text'
        )

        _arg_parser.add_argument('--source', type=str, default='',
                                 help='Source word')
        _arg_parser.add_argument('--target', type=str, default='',
                                 help='Target word')
        _arg_parser.add_argument('string', type=str,
                                 help='Source string')

        args = _arg_parser.parse_args(sys.argv[2:])

        print('Execute replace command with following arguments:\n'\
              '  string: {}, source: {}, target: {}'.format(
            args.string, args.source, args.target
        ))

        print('Result is:', self._text_processor.replace(
            args.string, args.source, args.target
        ))

    def reverse(self):
        _arg_parser = argparse.ArgumentParser(
            description='Print text in reverse order'
        )

        _arg_parser.add_argument('string', type=str,
                                 help='Source string')

        args = _arg_parser.parse_args(sys.argv[2:])

        print('Execute reverse command with following arguments:\n'\
              '  string: {}'.format(args.string))

        print('Result is: {}'.format(self._text_processor.reverse(args.string)))

    def intersection(self):
        _arg_parser = argparse.ArgumentParser(
            description='Find word intersection of two texts'
        )

        _arg_parser.add_argument('string_1', type=str,
                                 help='First string')
        _arg_parser.add_argument('string_2', type=str,
                                 help='Second tring')

        args = _arg_parser.parse_args(sys.argv[2:])

        print('Execute intersection command with following arguments:\n'\
              '  string_1: {}, string_2: {}'.format(args.string_1, args.string_2))

        print('Result is: {}'.format(', '.join(
            self._text_processor.intersection(args.string_1, args.string_2)
        )))

    def length(self):
        _arg_parser = argparse.ArgumentParser(
            description='Print length of text'
        )

        _arg_parser.add_argument('string', type=str,
                                 help='Source string')

        args = _arg_parser.parse_args(sys.argv[2:])

        print('Execute length command with following arguments:\n'\
              '  string: {}'.format(args.string))

        print('Result is: {}'.format(self._text_processor.length(args.string)))


class TextProcessor:
    def substring(self, string, start, length):
        if (length):
            return string[start:start+length]
        else:
            return string[start:]

    def count(self, string, target):
        words = string.split(" ")
        res = 0
        for word in words:
            if target == word:
                res += 1
        return res

    def repeats(self, string):
        uniq_words = set(string.split(" "))
        rep_words = {}

        for word in uniq_words:
            num_reps = string.count(word)
            if num_reps > 1:
                rep_words[word] = num_reps

        return rep_words

    def replace(self, string, source, target):
        return string.replace(source, target)

    def reverse(self, string):
        words = string.split(" ")
        return " ".join(words[::-1])

    def intersection(self, string_1, string_2):
        uniq_1 = set(string_1.split(" "))
        uniq_2 = set(string_2.split(" "))
        return uniq_1 & uniq_2

    def length(self, string):
        return len(string)


if __name__ == '__main__':
    text_processor = TextProcessor()
    TextProcessorCmdInterface(text_processor)
