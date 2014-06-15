package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.OrderArchive;
import org.springframework.data.jpa.repository.JpaRepository;

public interface OrderArchiveRepo
        extends JpaRepository<OrderArchive, Integer> {
}
