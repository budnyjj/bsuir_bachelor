-- usage example
-- set @verification = title_verification(3);
-- select @verification;

delimiter endfunc
create function title_verification(
    _code int)
    returns varchar(25)
begin
    declare result varchar(25);
    declare _title varchar(25);
    select title from products
        where code = _code into _title;
    select _title
        regexp '^[^eEuUiIoOaA]{1}[[a-z]|[A-Z]]' into result;
    return result;
end;
endfunc
delimiter ;
