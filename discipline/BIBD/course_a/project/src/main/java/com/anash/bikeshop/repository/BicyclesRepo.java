package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.Bicycles;
import org.springframework.data.jpa.repository.JpaRepository;

public interface BicyclesRepo
        extends JpaRepository<Bicycles, Long> {
}
