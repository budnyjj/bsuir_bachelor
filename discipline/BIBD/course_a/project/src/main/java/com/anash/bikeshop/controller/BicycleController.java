package com.anash.bikeshop.controller;

import com.anash.bikeshop.entity.AvailableBicycle;
import com.anash.bikeshop.entity.Bicycle;
import com.anash.bikeshop.entity.Order;
import com.anash.bikeshop.entity.User;
import com.anash.bikeshop.entity.enums.OrderStatus;
import com.anash.bikeshop.entity.enums.UserRole;
import com.anash.bikeshop.service.AvailableBicycleService;
import com.anash.bikeshop.service.BicycleService;
import com.anash.bikeshop.service.OrderService;
import com.anash.bikeshop.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.support.SessionStatus;
import org.springframework.web.servlet.ModelAndView;

import java.util.Date;

@Controller
public class BicycleController {

    @Autowired
    private BicycleService bicycleService;

    @Autowired
    private AvailableBicycleService availableBicycleService;

    @Autowired
    private OrderService orderService;

    @Autowired
    private UserService userService;

    @RequestMapping(value = "/catalog/{id}", method = RequestMethod.GET)

    public ModelAndView bicycleDetail(@PathVariable Integer id) {
        ModelAndView modelAndView = new ModelAndView("bicycle_details");

        Bicycle bicycle = bicycleService.findById(id);
        modelAndView.addObject("bicycle", bicycle);

        return modelAndView;
    }

    @RequestMapping(value = "/catalog/{id}/order", method = RequestMethod.GET)
    public ModelAndView bicycleOrder(@PathVariable Integer id) {
        ModelAndView modelAndView = new ModelAndView("order");

        Bicycle bicycle = bicycleService.findById(id);
        modelAndView.addObject("bicycle", bicycle);

        User user = new User();
        user.setEmail("test@email.com");
        user.setPhoneNumber("3335566");
        modelAndView.addObject("user", user);

        System.out.println("page loaded!");

        return modelAndView;
    }

    @RequestMapping(value = "/catalog/{id}/order", method = RequestMethod.POST)
    public String orderButtonPressed(
            @ModelAttribute("user") User user,
            @PathVariable Integer id,
            BindingResult result,
            SessionStatus status) {

        AvailableBicycle availableBicycle =
                availableBicycleService.findAvailableBicycleByBicycleId(id);

        if (availableBicycle != null) {
            user.setUserRole(UserRole.USER);
            user.setName("TEST");
            userService.save(user);

            Order order = new Order();
            order.setUser(user);
            order.setBicycle(bicycleService.findById(id));
            Date date = new Date();
            order.setOrderDate(new java.sql.Date(date.getTime()));
            order.setGoodsCost(bicycleService.findById(id).getPrice());
            order.setOrderStatus(OrderStatus.PROCESSING);
            orderService.save(order);

            availableBicycle.setCount(availableBicycle.getCount() - 1);
            AvailableBicycle curBicycle = availableBicycleService.save(availableBicycle);


            /*
            if (!availableBicycle.getAvailability()) {
                availableBicycleService.delete(curBicycle.getId());
            }
            */

        }

        status.setComplete();
        return "redirect:order";
    }

}