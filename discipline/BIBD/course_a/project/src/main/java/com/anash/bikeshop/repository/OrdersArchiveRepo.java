package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.OrdersArchive;
import org.springframework.data.jpa.repository.JpaRepository;

public interface OrdersArchiveRepo
        extends JpaRepository<OrdersArchive, Long> {
}
