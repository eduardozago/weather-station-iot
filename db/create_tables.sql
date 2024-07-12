-- Table: public.sensor_type

-- DROP TABLE IF EXISTS public.sensor_type;

CREATE TABLE IF NOT EXISTS public.sensor_type
(
    pk integer NOT NULL DEFAULT nextval('sensor_type_pk_seq'::regclass),
    name character varying(250) COLLATE pg_catalog."default" NOT NULL,
    insert_time timestamp with time zone DEFAULT CURRENT_TIMESTAMP,
    update_time timestamp with time zone DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT sensor_type_pkey PRIMARY KEY (pk)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.sensor_type
    OWNER to "[user]";

-- Trigger: update_timestamp_trig

-- DROP TRIGGER IF EXISTS update_timestamp_trig ON public.sensor_type;

CREATE OR REPLACE TRIGGER update_timestamp_trig
    BEFORE UPDATE 
    ON public.sensor_type
    FOR EACH ROW
    EXECUTE FUNCTION public.update_timestamp();


-- Table: public.sensors_info

-- DROP TABLE IF EXISTS public.sensors_info;

CREATE TABLE IF NOT EXISTS public.sensors_info
(
    pk bigint NOT NULL DEFAULT nextval('sensors_info_pk_seq'::regclass),
    st integer NOT NULL,
    val double precision,
    ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT sensors_info_pkey PRIMARY KEY (pk),
    CONSTRAINT st_fk FOREIGN KEY (st)
        REFERENCES public.sensor_type (pk) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE RESTRICT
        NOT VALID
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.sensors_info
    OWNER to "[user]";
-- Index: ts_brin_idx

-- DROP INDEX IF EXISTS public.ts_brin_idx;

CREATE INDEX IF NOT EXISTS ts_brin_idx
    ON public.sensors_info USING brin
    (ts)
    TABLESPACE pg_default;

-- Trigger: check_insert_time_trig

-- DROP TRIGGER IF EXISTS check_insert_time_trig ON public.sensors_info;

CREATE OR REPLACE TRIGGER check_insert_time_trig
    BEFORE INSERT
    ON public.sensors_info
    FOR EACH ROW
    EXECUTE FUNCTION public.check_insert_time();

-- Trigger: prevent_update_trig

-- DROP TRIGGER IF EXISTS prevent_update_trig ON public.sensors_info;

CREATE OR REPLACE TRIGGER prevent_update_trig
    BEFORE UPDATE 
    ON public.sensors_info
    FOR EACH STATEMENT
    EXECUTE FUNCTION public.prevent_update();
