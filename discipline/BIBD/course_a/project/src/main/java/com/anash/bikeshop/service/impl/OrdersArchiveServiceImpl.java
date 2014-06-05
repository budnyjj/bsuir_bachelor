package com.anash.bikeshop.service.impl;

import com.anash.bikeshop.entity.OrdersArchive;
import com.anash.bikeshop.repository.OrdersArchiveRepo;
import com.anash.bikeshop.service.OrdersArchiveService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class OrdersArchiveServiceImpl implements OrdersArchiveService {

    @Autowired
    private OrdersArchiveRepo ordersArchiveRepo;

    @Override
    public void save(OrdersArchive ordersArchive) {
        ordersArchiveRepo.saveAndFlush(ordersArchive);
    }

    @Override
    public void update(OrdersArchive ordersArchive) {
        ordersArchiveRepo.saveAndFlush(ordersArchive);
    }

    @Override
    public void delete(OrdersArchive ordersArchive) {
        ordersArchiveRepo.delete(ordersArchive);
    }

    @Override
    public OrdersArchive getById(long id) {
        return ordersArchiveRepo.findOne(id);
    }
}
