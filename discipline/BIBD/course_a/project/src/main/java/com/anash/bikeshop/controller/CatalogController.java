package com.anash.bikeshop.controller;

import com.anash.bikeshop.entity.Bicycle;
import com.anash.bikeshop.service.AvailableBicycleService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

import java.util.List;

@Controller
public class CatalogController {

    @Autowired
    private AvailableBicycleService availableBicyclesService;

    @RequestMapping(value = "/catalog")
    public ModelAndView listOfAvailableBicycles() {
        ModelAndView modelAndView = new ModelAndView();
        List<Bicycle> bicycles = availableBicyclesService.getAvailableBicyclesList();
        modelAndView.addObject("bicycles", bicycles);

        return modelAndView;
    }
}
