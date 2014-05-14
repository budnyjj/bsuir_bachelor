-- usage example
-- set @search = search_in_title(0); select @search;

delimiter endfunc
create function search_in_title(
    _code int)
    returns varchar(25)
begin
    declare result varchar(25);
    declare _title varchar(25);
    select title from products
        where code = _code into _title;
    select _title
        regexp '(e[sa])|(le)' into result;
    return result;
end;
endfunc
delimiter ;
