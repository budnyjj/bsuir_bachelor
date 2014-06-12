package com.anash.bikeshop.service.impl;

import com.anash.bikeshop.entity.Orders;
import com.anash.bikeshop.repository.OrdersRepo;
import com.anash.bikeshop.service.OrdersService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class OrdersServiceImpl implements OrdersService {

    @Autowired
    private OrdersRepo ordersRepo;

    @Override
    public void create(Orders orders) {
        ordersRepo.saveAndFlush(orders);
    }

    @Override
    public void update(Orders orders) {
        ordersRepo.saveAndFlush(orders);
    }

    @Override
    public void delete(Orders orders) {
        ordersRepo.saveAndFlush(orders);
    }

    @Override
    public Orders getById(long id) {
        return ordersRepo.findOne(id);
    }

    @Override
    public List<Orders> getAll() {
        return ordersRepo.findAll();
    }
}