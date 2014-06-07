package com.anash.bikeshop.service;

public interface Service<Type> {

    void create(Type entity);

    void update(Type entity);

    void delete(Type entity);

    Type getById(long id);
}
