package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.Bicycles;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface BicyclesRepo
        extends JpaRepository<Bicycles, Long> {
}
