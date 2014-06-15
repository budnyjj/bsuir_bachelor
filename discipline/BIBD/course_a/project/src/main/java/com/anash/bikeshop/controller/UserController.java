package com.anash.bikeshop.controller;

import com.anash.bikeshop.entity.User;
import com.anash.bikeshop.service.UserService;
import com.anash.bikeshop.entity.Bicycle;
import com.anash.bikeshop.service.BicycleService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;

import java.util.List;

@Controller
public class UserController {

    @Autowired
    private BicycleService bicycleService;

    @Autowired
    private UserService userService;

    @RequestMapping(value = "/user/{id}", method = RequestMethod.GET)
    public ModelAndView bicycleDetail(@PathVariable Long id) {
        ModelAndView modelAndView = new ModelAndView("user_details");

        User user = usersService.getById(id);
        modelAndView.addObject("user", user);

        Bicycle bicycle = bicycleService.getById(id);
        modelAndView.addObject("bicycle", bicycle);

        return modelAndView;
    }
}

