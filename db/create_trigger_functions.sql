-- FUNCTION: public.check_insert_time()

-- DROP FUNCTION IF EXISTS public.check_insert_time();

CREATE OR REPLACE FUNCTION public.check_insert_time()
    RETURNS trigger
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE NOT LEAKPROOF
AS $BODY$
begin
	if NEW.ts > CURRENT_TIMESTAMP then
		raise exception 'The ts % is after now', 
	    NEW.ts;
		return NULL;
	end if;
	return NEW;
end
$BODY$;

ALTER FUNCTION public.check_insert_time()
    OWNER TO "[user]";


-- FUNCTION: public.prevent_update()

-- DROP FUNCTION IF EXISTS public.prevent_update();

CREATE OR REPLACE FUNCTION public.prevent_update()
    RETURNS trigger
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE NOT LEAKPROOF
AS $BODY$
begin 
    raise exception 'Cant update table %s.', tg_table_name;
    return null;
end; 
$BODY$;

ALTER FUNCTION public.prevent_update()
    OWNER TO "[user]";


-- FUNCTION: public.update_timestamp()

-- DROP FUNCTION IF EXISTS public.update_timestamp();

CREATE OR REPLACE FUNCTION public.update_timestamp()
    RETURNS trigger
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE NOT LEAKPROOF
AS $BODY$
BEGIN
   NEW.update_time = CURRENT_TIMESTAMP; 
   RETURN NEW;
END;
$BODY$;

ALTER FUNCTION public.update_timestamp()
    OWNER TO "[user]";
