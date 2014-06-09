package com.anash.bikeshop.controller;

import com.anash.bikeshop.entity.Users;
import com.anash.bikeshop.service.UsersService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;

import java.util.List;

@Controller
@RequestMapping(value = "/user")
public class UserController {

    @Autowired
    private UsersService usersService;

    @RequestMapping(value = "/add", method = RequestMethod.GET)
    public ModelAndView addUsersPage() {
        ModelAndView modelAndView = new ModelAndView("add-user-form");
        modelAndView.addObject("user", new Users());
        return modelAndView;
    }
    /**/
            @RequestMapping(value = "/add", method = RequestMethod.POST)
            public ModelAndView addingUser(@ModelAttribute Users user) {
                ModelAndView modelAndView = new ModelAndView("index");
                //user.setRole(UserRole.USER);
                //usersService.create(user);

                String message = "User was successfully added.";
                modelAndView.addObject("message", message);

                return modelAndView;
            }

    @RequestMapping(value = "/list")
    public ModelAndView listOfUsers() {
        ModelAndView modelAndView = new ModelAndView("list-of-users");

        List<Users> users = usersService.getAll();
        modelAndView.addObject("users", users);

        return modelAndView;
    }

    @RequestMapping(value = "/delete/{id}", method = RequestMethod.GET)
    public ModelAndView deleteUser(@PathVariable Long id) {
        ModelAndView modelAndView = new ModelAndView("index");
        Users user = usersService.getById(id);
        usersService.delete(user);

        String message = "User was successfully deleted.";
        modelAndView.addObject("message", message);

        return modelAndView;
    }

}
