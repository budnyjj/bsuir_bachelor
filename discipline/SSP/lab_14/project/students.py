#!/usr/bin/env python

import functools

class Student:
    fields = [
        {'str': 'First name',   'repr': 'first_name', 'constraint': str},
        {'str': 'Last name',    'repr': 'last_name',  'constraint': str},
        {'str': 'Group number', 'repr': 'group',      'constraint': int}
    ]

    def __init__(self, *field_values):
        for field,field_value in zip(self.fields, field_values):
            field_name = field['repr']
            self.__dict__[field_name] = str(field_value)

    def __str__(self):
        # determine length of maximal field name
        len_name = lambda field: len(field['str'])
        max_len_name = len_name(max(self.fields, key=len_name))

        res = []
        for field in self.fields:
            res_fmt = '{:>' + str(max_len_name) +'}: {}'
            res.append(res_fmt.format(field['str'], getattr(self, field['repr'])))

        return '\n'.join(res)

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
        except ValueError:
            print('E: Could not convert "{}" to {}'.format(res, constraint))
            print('   Please, try again')
        except Exception:
            print('E: Unknown error occured')
            print('   Please, try again')
        else:
            return checked

def input_object(cls):
    fields = []
    for field in cls.fields:
        field_value = input_checked(field['str'], field['constraint'])
        fields.append(field_value)
    return cls(*fields)

def repl(handlers):
    while True:
        print('0. Exit')

        # show available commands
        cur_idx = 1
        for command in commands:
            print('{}. {}'.format(cur_idx, command[0]))
            cur_idx += 1

        choice = input_checked('Your choice', int)

        if choice == 0:
            # exit
            print('Bye.')
            return
        elif choice >= 1 and choice <= len(commands):
            # correct variant, so invoke handler
            handlers[choice-1][1]()
        else:
            # incorrect variant
            print('E: Please, choose suitable menu item')

        print()

def add_object(cls, lst):
    '''
    Input and append object to list
    '''
    obj = input_object(cls)
    lst.append(obj)

def list_fields(key_field, lst):
    '''
    Show field value of each element in list
    '''
    if len(lst) == 0:
        print('I: There is no objects in list')
        return

    for idx,obj in enumerate(lst):
        print('{}. {}'.format(idx+1, getattr(obj, key_field)))

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
            print(lst[choice-1])
            break
        else:
            # incorrect choice
            print('E: Please, choose suitable menu item')




if __name__ == '__main__':
    students = []
    commands = (
        ('Add student', functools.partial(add_object, Student, students)),
        ('List students', functools.partial(list_fields, 'last_name', students)),
        ('Show student', functools.partial(show_object, 'last_name', students)),
    )
    repl(commands)
