package com.anash.bikeshop.service;

import java.util.List;

public interface Service<Type> {

    Type save(Type entity);

    // void update(Type entity);

    void delete(Integer id);

    Type findById(Integer id);

    List<Type> getAll();
}
