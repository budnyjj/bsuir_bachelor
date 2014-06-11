package com.anash.bikeshop.controller;

import com.anash.bikeshop.entity.Bicycles;
import com.anash.bikeshop.service.AvailableBicyclesService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

import java.util.ArrayList;
import java.util.List;

@Controller
public class CatalogController {

    @Autowired
    private AvailableBicyclesService availableBicyclesService;

    @RequestMapping(value = "/catalog")
    public ModelAndView listOfAvailableBicycles() {
        ModelAndView modelAndView = new ModelAndView();
        List<Bicycles> bicycles = availableBicyclesService.getAvailableBicyclesList();
        modelAndView.addObject("bicycles", bicycles);

        ArrayList<String> bicycleNames = null;
        StringBuffer buffer = new StringBuffer();

        for (Bicycles bicycle : bicycles) {
            buffer.setLength(0);
            buffer.append(bicycle.getManufacturer() + " ");
            buffer.append(bicycle.getProductName() + " (");
            buffer.append(bicycle.getYear() + ")");

            bicycleNames.add(buffer.toString());
        }
        modelAndView.addObject("bicycleNames", bicycleNames);

        return modelAndView;
    }
}
