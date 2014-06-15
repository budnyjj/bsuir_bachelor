package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.Order;
import org.springframework.data.jpa.repository.JpaRepository;

public interface OrderRepo
        extends JpaRepository<Order, Integer> {
}
