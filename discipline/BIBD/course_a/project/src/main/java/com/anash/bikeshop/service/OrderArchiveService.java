package com.anash.bikeshop.service;

import com.anash.bikeshop.entity.OrderArchive;

import java.util.List;

public interface OrderArchiveService extends Service<OrderArchive> {

List<OrderArchive> getOrdersByUserId(Integer id);

}
