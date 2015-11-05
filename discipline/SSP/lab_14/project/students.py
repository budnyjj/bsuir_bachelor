#!/usr/bin/env python

import argparse
import functools
import json
import re

class Constraints:
    _PATTERN_NAME = '[A-Z][a-z]*'
    _PATTERN_GROUP = '[0-9]{5,6}'

    @classmethod
    def isName(cls, s):
        if re.fullmatch(cls._PATTERN_NAME, s):
            return s
        else:
            raise ValueError(
                'The name should be specified in format {}'.format(
                    cls._PATTERN_NAME
                )
            )

    @classmethod
    def isGroupNumber(cls, s):
        if re.fullmatch(cls._PATTERN_GROUP, s):
            return s
        else:
            raise ValueError(
                'The group should be specified in format {}'.format(
                    cls._PATTERN_GROUP
                )
            )

class Student:
    fields = (
        {
            'str': 'First name',
            'repr': 'first_name',
            'constraint': Constraints.isName
        },
        {
            'str': 'Last name',
            'repr': 'last_name',
            'constraint': Constraints.isName
        },
        {
            'str': 'Group number',
            'repr': 'group',
            'constraint': Constraints.isGroupNumber
        }
    )

    @classmethod
    def fromJSON(cls, j_str):
        fields = json.loads(j_str)
        return cls(**fields)

    def __init__(self, **fields):
        cstr_field_names = [f['repr'] for f in self.fields]
        cstr_field_constraints = { f['repr']: f['constraint'] for f in self.fields }

        for field_name,field_value in fields.items():
            if field_name in cstr_field_names:
                self.__dict__[field_name] =\
                    cstr_field_constraints[field_name](field_value)
            else:
                raise ValueError('Cannot construct object from {}'.format(fields))

    def __str__(self):
        # determine length of maximal field name
        len_name = lambda field: len(field['str'])
        max_len_name = len_name(max(self.fields, key=len_name))

        res = []
        for field in self.fields:
            res_fmt = '{:>' + str(max_len_name) +'}: {}'
            res.append(res_fmt.format(field['str'], getattr(self, field['repr'])))

        return '\n'.join(res)

    def toJSON(self):
        return json.dumps(self.__dict__)

def input_checked(prompt_msg, constraint):
    '''
    Asks user to input value and perform correctness check
    '''
    def input_basic():
        return input('{}: '.format(prompt_msg))

    res = ''
    while True:
        res = input_basic()
        try:
            checked = constraint(res)
        except Exception as e:
            print('E: {}'.format(e))
            print('   Please, try again')
        else:
            return checked

def input_object(cls):
    fields = {}
    for field in cls.fields:
        field_value = input_checked(field['str'], field['constraint'])
        fields[field['repr']] = field_value
    return cls(**fields)

def repl(handlers):
    while True:
        print('0. Exit')

        # show available commands
        cur_idx = 1
        for command in commands:
            print('{}. {}'.format(cur_idx, command[0]))
            cur_idx += 1

        print()
        choice = input_checked('Your choice', int)

        if choice == 0:
            # exit
            print('Bye.')
            return
        elif choice >= 1 and choice <= len(commands):
            print()
            # correct variant, so invoke handler
            handlers[choice-1][1]()
        else:
            # incorrect variant
            print('E: Please, choose suitable menu item')

        print()

#
# REPL handlers
#

def add_object(cls, lst):
    '''
    Input and append object to list
    '''
    obj = input_object(cls)
    lst.append(obj)

def show_object(key_field, lst):
    '''
    Show field value of each element in list
    '''
    if len(lst) == 0:
        print('I: There are no objects in list')
        return

    while True:
        print('0. Exit')

        for idx,obj in enumerate(lst):
            print('{}. {}'.format(idx+1, getattr(obj, key_field)))

        choice = input_checked('Your choice', int)

        if choice == 0:
            # back
            break
        if choice >= 1 and choice <= len(lst):
            # correct choice
            print()
            print(lst[choice-1])
            break
        else:
            # incorrect choice
            print('E: Please, choose suitable menu item')

def save(lst, fname):
    if not fname:
        print('E: Filename was not specified')
        print('   Please, run this program with --file option')
        return

    with open(fname, 'w') as f:
        for obj in lst:
            f.write('{}\n'.format(obj.toJSON()))

def load(cls, lst):
    if not fname:
        print('E: Filename was not specified')
        print('   Please, run this program with --file option')
        return

    lst.clear()

    with open(fname, 'r') as f:
        for line in f:
            obj = None
            try:
                obj = cls.fromJSON(line)
            except Exception as e:
                print('E: {}'.format(e))
                print('   Invalid record format: {}'.format(line))
                break
            else:
                lst.append(obj)


if __name__ == '__main__':
    arg_parser = argparse.ArgumentParser(
        description = 'Student management demo program',
    )
    arg_parser.add_argument('--file', help='Students DB filename', required=False)
    args = arg_parser.parse_args()
    fname = args.file

    students = []
    commands = (
        ('Add student', functools.partial(add_object, Student, students)),
        ('Show students', functools.partial(show_object, 'last_name', students)),
        ('Save to file', functools.partial(save, students, fname)),
        ('Load from file', functools.partial(load, Student, students)),
    )
    repl(commands)
