package com.anash.bikeshop.controller;

import com.anash.bikeshop.entity.Bicycles;
import com.anash.bikeshop.service.BicycleService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;

@Controller
public class BicycleController {

    @Autowired
    private BicycleService bicycleService;

    @RequestMapping(value = "/catalog/detail/{id}", method = RequestMethod.GET)
    public ModelAndView bicycleDetail(@PathVariable Long id) {
        ModelAndView modelAndView = new ModelAndView("detail");

        Bicycles bicycle = bicycleService.getById(id);
        modelAndView.addObject("bicycle", bicycle);

        return modelAndView;
    }

}
