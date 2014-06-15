package com.anash.bikeshop.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

@Controller
public class LoginController {
    @RequestMapping(value = "/login")
    public ModelAndView userLogin() {
        ModelAndView modelAndView = new ModelAndView();
        return modelAndView;
    }
}
