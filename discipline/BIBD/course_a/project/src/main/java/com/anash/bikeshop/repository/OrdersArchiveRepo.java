package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.OrdersArchive;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface OrdersArchiveRepo
        extends JpaRepository<OrdersArchive, Long> {
}
