package com.anash.bikeshop.service;

import java.util.List;

public interface Service<Type> {

    void create(Type entity);

    void update(Type entity);

    void delete(Type entity);

    Type getById(long id);

    List<Type> getAll();
}
