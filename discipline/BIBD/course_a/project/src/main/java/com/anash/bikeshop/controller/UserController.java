package com.anash.bikeshop.controller;

import com.anash.bikeshop.entity.User;
import com.anash.bikeshop.service.UserService;
import com.anash.bikeshop.entity.Bicycle;
import com.anash.bikeshop.service.BicycleService;
import com.anash.bikeshop.entity.OrderArchive;
import com.anash.bikeshop.service.OrderArchiveService;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;

import java.util.ArrayList;
import java.util.List;

@Controller
public class UserController {

    @Autowired
    private BicycleService bicycleService;

    @Autowired
    private UserService userService;

    @Autowired
    private OrderArchiveService orderArchiveService;

    @RequestMapping(value = "/user/{id}", method = RequestMethod.GET)
    public ModelAndView userDetail(@PathVariable Integer id) {
        ModelAndView modelAndView = new ModelAndView("user_details");
        List<OrderArchive> orders = orderArchiveService.getOrdersByUserId(id);
        modelAndView.addObject("orders", orders);

        List<Bicycle> bicycles = new ArrayList<>();
        for (OrderArchive order: orders)
            bicycles.add(order.getBicycle());

        modelAndView.addObject("bicycles", bicycles);

        User user = userService.getById(id);
        modelAndView.addObject("user", user);

        return modelAndView;
    }
}

