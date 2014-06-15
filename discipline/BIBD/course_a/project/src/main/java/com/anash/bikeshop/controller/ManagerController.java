package com.anash.bikeshop.controller;

import com.anash.bikeshop.entity.Order;
import com.anash.bikeshop.service.OrderService;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;

import java.util.List;

@Controller
public class ManagerController {

    @Autowired
    private OrderService orderService;

    @RequestMapping(value = "/manager", method = RequestMethod.GET)
    public ModelAndView orderList() {
        ModelAndView modelAndView = new ModelAndView("manager");

        List<Order> orders = orderService.getAll();
        modelAndView.addObject("orders", orders);

        return modelAndView;
    }
}
