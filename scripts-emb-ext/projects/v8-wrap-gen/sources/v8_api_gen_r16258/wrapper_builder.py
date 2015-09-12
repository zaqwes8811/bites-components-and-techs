# coding: utf-8

# App
from v8_api_gen_r16258 import vectors
from v8_api_gen_r16258 import scalars
from parsers_cpp_code import header_handmade_parser


class BuilderV8AccessorsPackage(object):
    def __init__(self, type_and_var_list, source):
        self.type_and_var_list_ = type_and_var_list
        self.class_name_ = self.type_and_var_list_[0][2]
        self.source_ = source

    def get_v8_class_name(self):
        return self.class_name_ + 'V8'

    # ::Blueprint()
    @staticmethod
    def __do_blueprint_method_decl():
        return 'CreateOwnBlueprint(\n' + \
               '      v8::Isolate* isolate)'

    def blueprint_method_decl(self):
        return '  static v8::Handle<v8::ObjectTemplate> ' + self.__do_blueprint_method_decl() + ';'

    def blueprint_method_impl(self):
        result = 'v8::Handle<v8::ObjectTemplate> ' + self.get_v8_class_name() + '::CreateOwnBlueprint(\n' + \
                 '      v8::Isolate* isolate) \n  {\n'

        result += '  HandleScope handle_scope(isolate);\n' \
                  + '\n  Handle<ObjectTemplate> result = ObjectTemplate::New();\n' \
                  + '  result->SetInternalFieldCount(1);\n'

        # Connect Vectors
        for elem in self.type_and_var_list_:
            connect = vectors.MakerV8VectorFieldAccessor(*elem).connect_getters_and_setters()
            if connect:
                result += connect
                result += '\n'

        # Connect Scalars
        dec_wrappers = header_handmade_parser.ExtractorVarsDeclarations().extract_field_declarations(
            self.source_, self.class_name_)
        builder = scalars.MakerV8ScalarFieldAccessor()
        code = builder.do_scalar_connecters(dec_wrappers)
        for line in code:
            result += line+');\n'

        # Нужно правильно выйти
        result += '\n  return handle_scope.Close(result);\n'
        result += '}'

        return result

    # ::New()
    def __do_new_method_decl(self):
        return 'New(' + self.class_name_ + '* database, v8::Isolate *isolate)'

    def new_method_decl(self):
        return '  static v8::Handle<v8::Object> ' + self.__do_new_method_decl() + ';'

    def new_method_impl(self):
        return 'Handle<Object> ' + self.get_v8_class_name() + '::' + self.__do_new_method_decl() + ' {\n' + \
               '  HandleScope handle_scope(isolate);\n' + \
               '  Context::Scope scope(isolate->GetCurrentContext());\n' + \
               '\n' + \
               '  Handle<ObjectTemplate> raw_template = \n' + \
               '      CreateOwnBlueprint(isolate);    \n' + \
               '\n' + \
               '  Handle<ObjectTemplate> templ =\n' + \
               '      Local<ObjectTemplate>::New(isolate, raw_template);\n' + \
               '\n' + \
               '  Handle<Object> result = templ->NewInstance();\n' + \
               '  Handle<External> map_ptr = External::New(database);\n' + \
               '\n' + \
               '  result->SetInternalField(0, map_ptr);\n' + \
               '  return handle_scope.Close(result);\n' + \
               '}\n'

    # ::vectors
    def get_vector_decls(self):
        for elem in self.type_and_var_list_:
            builder = vectors.MakerV8VectorFieldAccessor(*elem)
            name = builder.make_zero_level_getter_decl()
            if name:
                yield '  static void ' + name + ';\n'

            setter_declaration = builder.make_last_level_setter_decl()
            if setter_declaration:
                yield '  static void ' + setter_declaration + ';\n'

            getter_declaration = builder.make_last_level_getter_decl()
            if getter_declaration:
                yield '  static void ' + getter_declaration + ';\n'

    def get_vector_impls(self):
        for elem in self.type_and_var_list_:
            builder = vectors.MakerV8VectorFieldAccessor(*elem)
            code = builder.make_zero_level_getter_impl()
            if code:
                yield code

            getter = builder.make_last_level_getter_impl()
            if getter:
                yield getter

            setter = builder.make_last_level_setter_impl()
            if setter:
                yield setter

    # ::Scalars
    def get_scalar_decls(self):
        # Нужно попробовать испольтовать новый парсер
        extractor = header_handmade_parser.ExtractorVarsDeclarations()
        items = extractor.extract_field_declarations(self.source_, self.class_name_)
        builder = scalars.MakerV8ScalarFieldAccessor()
        for elem in items:
            code = builder.make_getters_decl(elem)
            if code:
                yield code

            code = builder.make_setter_decl(elem)
            if code:
                yield code

    def get_scalar_impls(self):
        extractor = header_handmade_parser.ExtractorVarsDeclarations()
        items = extractor.extract_field_declarations(self.source_, self.class_name_)

        builder = scalars.MakerV8ScalarFieldAccessor()

        for elem in items:
            code = builder.make_getter_impl(elem, self.class_name_)
            if code:
                yield code

            code = builder.make_setter_impl(elem, self.class_name_)
            if code:
                yield code

    # ::Matrix

    # ::Functions



