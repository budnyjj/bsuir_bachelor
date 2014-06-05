package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.Orders;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface OrdersRepo
        extends JpaRepository<Orders, Long> {
}
