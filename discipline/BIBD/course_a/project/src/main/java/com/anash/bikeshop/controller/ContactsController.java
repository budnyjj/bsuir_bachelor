package com.anash.bikeshop.controller;

import com.anash.bikeshop.entity.Bicycles;
import com.anash.bikeshop.service.AvailableBicyclesService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

import java.util.List;

@Controller
public class ContactsController {
    @RequestMapping(value = "/contacts")
    public ModelAndView showContacts() {
        ModelAndView modelAndView = new ModelAndView();
        return modelAndView;
    }
}
