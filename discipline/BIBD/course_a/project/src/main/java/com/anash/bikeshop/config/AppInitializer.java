package com.anash.bikeshop.config;


import org.springframework.web.servlet.support.AbstractAnnotationConfigDispatcherServletInitializer;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;

import static org.lightadmin.core.util.LightAdminConfigurationUtils.*;

public class AppInitializer extends AbstractAnnotationConfigDispatcherServletInitializer {
    @Override
    public void onStartup(ServletContext servletContext) throws ServletException {

        servletContext.setInitParameter(
                LIGHT_ADMINISTRATION_BASE_URL, "/admin"
        );
        servletContext.setInitParameter(
                LIGHT_ADMINISTRATION_BACK_TO_SITE_URL, "/catalog"
        );
        servletContext.setInitParameter(
                LIGHT_ADMINISTRATION_BASE_PACKAGE, "com.anash.bikeshop.admin"
        );

        super.onStartup(servletContext);
    }

    @Override
    protected Class<?>[] getRootConfigClasses() {
        return new Class<?>[]{
                DataConfig.class
        };
    }

    @Override
    protected Class<?>[] getServletConfigClasses() {
        return new Class<?>[] {
                WebConfig.class
        };
    }

    @Override
    protected String[] getServletMappings() {
        return new String[] { "/" };
    }
}
