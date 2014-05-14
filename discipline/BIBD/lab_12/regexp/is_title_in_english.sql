-- usage example
-- set @english = is_title_in_english(0); select @english;

delimiter endfunc
create function is_title_in_english(
    _code int)
    returns varchar(25)
begin
    declare result varchar(25);
    declare _title varchar(25);
    select title from products
        where code = _code into _title;
    select _title
        regexp '[a-zA-Z]' into result;
    return result;
end;
endfunc
delimiter ;
