package com.anash.bikeshop.service.impl;

import com.anash.bikeshop.entity.Order;
import com.anash.bikeshop.repository.OrderRepo;
import com.anash.bikeshop.service.OrderService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class OrderServiceImpl implements OrderService {

    @Autowired
    private OrderRepo orderRepo;

    @Override
    public void create(Order order) {
        Order createdOrder = order;
        orderRepo.saveAndFlush(createdOrder);
    }

    @Override
    public void update(Order orders) {
        orderRepo.saveAndFlush(orders);
    }

    @Override
    public void delete(Order orders) {
        orderRepo.saveAndFlush(orders);
    }

    @Override
    public Order getById(Integer id) {
        return orderRepo.findOne(id);
    }

    @Override
    public List<Order> getAll() {
        return orderRepo.findAll();
    }
}
